#ifndef __WIFI_AP_H__
#define __WIFI_AP_H__

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

#include "Drivers.h"

void generateAP(void);
void handleRoot(void);
void handleSetWiFi(void);
void server_handleClient(void);

#endif