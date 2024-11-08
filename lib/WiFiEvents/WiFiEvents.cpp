#include "WiFiEvents.h"

String ssid = "";
String password = "";
const char* updateUrlBase = UPDATE_URL_BASE;
const char* latestUrlBase  = LATEST_URL_BASE;

bool melodyPlaying = false;
bool reminderState = false;
int currentAlarm = 0;
int id = 1;

bool startTimerOffLed = false;
uint32_t past_timerOffLed = 0;
uint32_t diff_timerOffLed = 0;
uint8_t num_repeat_melody = 1;
uint8_t count_repeat_melody = 0;

void connectToWiFi() {
  bool is_wifi_connect = false;

  Serial.println();
  Serial.print("Connecting to WiFi: " + ssid);
  Lcd.clear();
  Lcd.setCursor(0, 0);
  Lcd.print(" Conectando.... ");

  //Obtener SSID y PASSWORD de EEPROM
  ssid = EEPROM.readString(ADDR_SSID_TO_CONNECT);
  password = EEPROM.readString(ADDR_PASS_TO_CONNECT);

  WiFi.begin(ssid.c_str(), password.c_str());
  //WiFi.begin(ssid, password);

  uint8_t count_error_wifi_connect = 0;
  Serial.println("SSID: " + ssid);
  Serial.println("PASSWORD: " + password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if(count_error_wifi_connect >= MAX_ERROR_WIFI_NO_CONNECT) {
      is_wifi_connect = false;
      break;
    }
    is_wifi_connect = true;
    count_error_wifi_connect++;
  }
  Serial.println();

  if( is_wifi_connect ) {
    // Conexión WiFi establecida
    Lcd.clear();
    Lcd.setCursor(0, 0);
    Lcd.print("   Conectado!   ");
    delay(1000);
    //Lcd.noBacklight();

    Serial.println("Connected to WiFi: " + ssid);
  }
  else {
     // Conexión WiFi establecida
    Lcd.clear();
    Lcd.setCursor(0, 0);
    Lcd.print("  NO CONECTADO  ");
    Lcd.setCursor(0, 1);
    Lcd.print("  set new red!  ");
    //Lcd.noBacklight();

    Serial.println("NO CONECTADO, configure nueva red");
    delay(3000);
  }

  //return is_wifi_connect;
}

void updateWiFiCredentials(String newSSID, String newPASS) {
  ssid = newSSID;
  password = newPASS;
  connectToWiFi();
}

void sendStatusUpdate(bool isEmpty, bool almostEmpty) {
  if (WiFi.status() != WL_CONNECTED) return;

  String updateUrl = String(updateUrlBase) + "/" + id;
  HTTPClient http;
  http.begin(updateUrl);  // Usa la URL correcta para actualizar el estado
  http.addHeader("Content-Type", "application/json");

  DynamicJsonDocument jsonDoc(200);

  jsonDoc["id"] = 1;
  jsonDoc["isEmpty"] = isEmpty;
  jsonDoc["almostEmpty"] = almostEmpty;
  //jsonDoc["reminder"] = reminder; //Evaluar lógica de cambio de reminder

  String jsonString;
  serializeJson(jsonDoc, jsonString);

  int httpResponseCode = http.sendRequest("PATCH", jsonString);

  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println(httpResponseCode);
    Serial.println(response);
  } else {
    Serial.print("Error on sending PATCH: ");
    Serial.println(httpResponseCode);
  }

  http.end();
}

void sendStatusReminder(bool reminder) {
  if (WiFi.status() != WL_CONNECTED) return;

  String updateUrl = String(updateUrlBase) + "/" + id;
  HTTPClient http;
  http.begin(updateUrl);  // Usa la URL correcta para actualizar el estado
  http.addHeader("Content-Type", "application/json");

  DynamicJsonDocument jsonDoc(200);

  jsonDoc["id"] = 1;
  jsonDoc["reminder"] = reminder;

  String jsonString;
  serializeJson(jsonDoc, jsonString);

  int httpResponseCode = http.sendRequest("PATCH", jsonString);

  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println(httpResponseCode);
    Serial.println(response);
  } else {
    Serial.print("Error on sending PATCH: ");
    Serial.println(httpResponseCode);
  }

  http.end();
}

void updateWeight(double peso) {
  if (WiFi.status() != WL_CONNECTED) return;

  String updateUrl = String(updateUrlBase) + "/" + id;
  HTTPClient http;
  http.begin(updateUrl);
  http.addHeader("Content-Type", "application/json");

  DynamicJsonDocument jsonDoc(200);

  jsonDoc["id"] = 1;
  jsonDoc["value"] = String(peso, 2);

  String jsonString;
  serializeJson(jsonDoc, jsonString);

  int httpResponseCode = http.sendRequest("PATCH", jsonString);

  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println(httpResponseCode);
    Serial.println(response);
  } else {
    Serial.print("Error on sending PATCH: ");
    Serial.println(httpResponseCode);
  }

  http.end();
}

void checkReminder(bool isEmpty, bool almostEmpty) {
  if (WiFi.status() != WL_CONNECTED) return;

  String latestUrl = String(latestUrlBase) + "/" + id;
  HTTPClient http;
  http.begin(latestUrl);
  int httpResponseCode = http.GET();

  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println(httpResponseCode);
    Serial.println(response);

    DynamicJsonDocument jsonDoc(1024);
    deserializeJson(jsonDoc, response);

    bool reminder = jsonDoc["reminder"];
    int numberAlarm = jsonDoc["numberAlarm"];

    Lcd.clear();
    
    if (reminder) {
      startTimerOffLed = true;
      Lcd.backlight();
      Lcd.setCursor(0, 0);
      Lcd.print(" Tomar medicina ");
      Lcd.setCursor(0, 1);
      melodyPlaying = true;
      setColor(0, 0, 255);
    } else if (isEmpty) {
      Lcd.backlight();
      Lcd.setCursor(0, 0);
      Lcd.print(" Sin pastillas ");
      setColor(255, 0, 0); // Activar LED rojo
    } else if (almostEmpty) {
      Lcd.backlight();
      Lcd.setCursor(0, 0);
      Lcd.print("   Casi vacio   ");
      setColor(255, 255, 0); // Activar LED amarillo
    } else {
      Lcd.setCursor(0, 0);
      Lcd.noBacklight();
      setColor(0, 0, 0); // Apagar todos los LEDs
    }

    //delay(1000);  // Delay opcional para la visualización en la Lcd

    if (currentAlarm != numberAlarm && reminder) {
      currentAlarm = numberAlarm;
      if (melodyPlaying) {
        noTone(PIN_BUZZ);
        melodyPlaying = false;
      }
    }

    if (reminder) {
      setColor(0, 0, 255); // Azul para reminder activo
      melodyPlaying = true;
      
      num_repeat_melody = (currentAlarm==1)?3:1;  //Numero de veces a repetir melody

      if( count_repeat_melody < num_repeat_melody ) {
        switch (currentAlarm) {
          case 1: alarmTone(PIN_BUZZ);          break;
          case 2: playMelodyTwinkle(PIN_BUZZ);  break;
          case 3: playFurElise(PIN_BUZZ);       break;
          case 4: playNokiaTune(PIN_BUZZ);      break;
          case 5: music_wars(PIN_BUZZ);         break;
          default: melodyPlaying = false;       break;
        }
        count_repeat_melody++;
      }

    } 
    else {
      if (reminderState) {
        noTone(PIN_BUZZ);
        melodyPlaying = false;
        setColor(0, 0, 0);
        reminderState = false;
      }
      past_timerOffLed = millis();
      count_repeat_melody = 0;
    }

    // Si todos los estados son falsos, apagar el LED
    if (!reminder && !isEmpty && !almostEmpty) {
      setColor(0, 0, 0); // Apagar el LED
    }

  } else {
    Serial.print("Error on sending GET: ");
    Serial.println(httpResponseCode);
  }

  http.end();

  /* CLEAR REMINDER */
  if( startTimerOffLed ) {
    diff_timerOffLed = millis() - past_timerOffLed;
    if( diff_timerOffLed >= TIME_OFF_LED_LCD ) {
      delay(100);
      sendStatusReminder(false);
      startTimerOffLed = false;
    }
  }

}
