#ifndef __WIFIEVENTS_H__
#define __WIFIEVENTS_H__

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#include "Drivers.h"
#include "Melodies.h"

void connectToWiFi(void);//OK
void updateWiFiCredentials(String newSSID, String newPASS);//OK
void sendStatusUpdate(bool isEmpty, bool almostEmpty);//OK
void sendStatusReminder(bool reminder);
void updateWeight(double peso);//OK
void checkReminder(bool isEmpty, bool almostEmpty);//OK

#endif