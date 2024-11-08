#include <Arduino.h>
#include "Melodies.h"
#include "WiFiEvents.h"
#include "WiFi_AP.h"
#include "Drivers.h"

double previousWeight = -1;
double pesoFinal = 0;
bool isEmpty = false;
bool almostEmpty = false;

uint32_t time_past = millis();
uint32_t time_dT = 0;
uint32_t time_current = 0;

void setup( ) {
  sys_configuration( );
  connectToWiFi( );
  generateAP( );
}

void loop( ) {

  bool isWiFiConnected = (WiFi.status() == WL_CONNECTED);

  if (!isWiFiConnected) {
    Lcd.backlight();
    Lcd.clear();
    Lcd.setCursor(0, 0);
    Lcd.print("  Sin conexion  ");
    connectToWiFi( );
  } 
  else {

    time_current = millis();
    time_dT = time_current - time_past;

    if( time_dT >= 1000 ) { //RETARDO DE 1 SEGUNDO NO BLOQUEANTE
      time_past = millis();
      //Lcd.noBacklight();
      pesoFinal = Balanza.get_units(10)*1000;

      Serial.print("Peso: ");
      Serial.print(pesoFinal);
      Serial.println(" mg");

      // Verificar y actualizar los estados isEmpty y almostEmpty
      bool newIsEmpty = (pesoFinal < 300.0);
      bool newAlmostEmpty = (pesoFinal <= 2000 && pesoFinal > 300);

      if (newIsEmpty != isEmpty || newAlmostEmpty != almostEmpty) {
        isEmpty = newIsEmpty;
        almostEmpty = newAlmostEmpty;
        sendStatusUpdate(isEmpty, almostEmpty);
      }

      if (!newIsEmpty && isEmpty) {
        isEmpty = false;
        sendStatusUpdate(isEmpty, almostEmpty);
      }

      if (!newAlmostEmpty && almostEmpty) {
        almostEmpty = false;
        sendStatusUpdate(isEmpty, almostEmpty);
      } 

      if (pesoFinal != previousWeight) {
        updateWeight(pesoFinal);
        previousWeight = pesoFinal;
      }


      checkReminder(isEmpty,almostEmpty);
    }

    //delay(1000);
  }

  server_handleClient();

  delay(1);
}
