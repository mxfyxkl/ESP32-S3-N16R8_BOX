#ifndef ALL_H
#define ALL_H

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Update.h>

extern WebServer server;
extern bool wifiConnected;
// Add your function declarations and definitions here

String getDeviceInfo();
int device_info();
int update();
int updateok();
int updatelogo();
int wifi();
int wifisteup();
#endif // ALL_H