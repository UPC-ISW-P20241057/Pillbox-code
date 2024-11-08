#ifndef __DRIVERS_H__
#define __DRIVERS_H__

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "HX711.h"
#include <EEPROM.h>

#define __DEBUG__

#ifdef __DEBUG__
  #define DBG_PRINT(x) Serial.print(x)
  #define DBG_PRINTLN(x) Serial.println(x)
#else
  #define DBG_PRINT(x)
  #define DBG_PRINTLN(x)
#endif

// PINES
#define PIN_DT 18
#define PIN_SCK 19
#define PIN_SDA 21
#define PIN_SCL 22
#define PIN_BUZZ 33
#define PIN_RGB_R 27
#define PIN_RGB_G 26
#define PIN_RGB_B 25

// LCD
#define LCD_I2C_ADDRESS 0x27
#define LCD_I2C_ROWS 16
#define LCD_I2C_COLS 2

// WiFi
//#define SSID_TO_CONNECT "HUAWEIP20"
//#define PASS_TO_CONNECT "contrasenia123@pastillero"
#define ADDR_SSID_TO_CONNECT 1
#define ADDR_PASS_TO_CONNECT 201
#define SSID_THIS "RED_PASTILLERO"
#define PASS_THIS "12345678"
#define UPDATE_URL_BASE "https://medibox-gateway-devel.azurewebsites.net/gateway/v1/weights/esp"
#define LATEST_URL_BASE "https://medibox-gateway-devel.azurewebsites.net/gateway/v1/weights"
#define MAX_ERROR_WIFI_NO_CONNECT 10

#define LOCAL_IP      192,168,1,32
#define LOCAL_GATEWAY 192,168,1,1
#define LOCAL_SUBNET  255,255,255,0

#define TIME_OFF_LED_LCD 5000 //Tiempo en segundos

// Extern
extern LiquidCrystal_I2C Lcd;
extern HX711 Balanza;

// Functions
void sys_configuration(void);
void setColor(int red, int green, int blue);

#endif