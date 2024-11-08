#include "Drivers.h"

LiquidCrystal_I2C Lcd(LCD_I2C_ADDRESS, LCD_I2C_ROWS, LCD_I2C_COLS);
HX711 Balanza;

void sys_configuration() {

  Serial.begin(115200);
  
  Lcd.init();
  Lcd.backlight();
  Lcd.setCursor(0, 0);
  Lcd.print("Inicializando...");

  Balanza.begin(PIN_DT, PIN_SCK);
  Balanza.set_scale(-835.886);
  Balanza.tare(); 
  
  pinMode(PIN_RGB_R, OUTPUT);
  pinMode(PIN_RGB_G, OUTPUT);
  pinMode(PIN_RGB_B, OUTPUT);
  pinMode(PIN_BUZZ, OUTPUT);

  EEPROM.begin(1024);

  delay(1000);

}

void setColor(int red, int green, int blue) {
  analogWrite(PIN_RGB_R, 255 - red);
  analogWrite(PIN_RGB_G, 255 - green);
  analogWrite(PIN_RGB_B, 255 - blue);
}