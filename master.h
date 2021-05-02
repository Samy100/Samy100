#ifndef MASTER_H
#define MASTER_H

#include <ArduinoBLE.h>
#include <WiFiNINA.h>
#include <NTPClient.h>
#include <RTCZero.h>
#include <ArduinoLowPower.h>
#include <ThingSpeak.h>

#define SECRET_SSID "Wifi network name"    // replace MySSID with your WiFi network name
#define SECRET_PASS "x" // replace MyPassword with your WiFi password
/*For zceeabi email*/
#define SECRET_CH_ID xxxxxxx      // replace 0000000 with your channel number
#define SECRET_WRITE_APIKEY "xxxxxxxx"   // replace XYZ with your channel write API Key
void device_setup();
void device_loop();

#endif
