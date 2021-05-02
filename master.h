#ifndef MASTER_H
#define MASTER_H

#include <ArduinoBLE.h>
#include <WiFiNINA.h>
#include <NTPClient.h>
#include <RTCZero.h>
#include <ArduinoLowPower.h>
#include <ThingSpeak.h>

#define SECRET_SSID "Click here for viruses"    // replace MySSID with your WiFi network name
#define SECRET_PASS "make10guesses" // replace MyPassword with your WiFi password
/*For zceeabi email*/
#define SECRET_CH_ID 1246813      // replace 0000000 with your channel number
#define SECRET_WRITE_APIKEY "HU5PWPWSCWEQOC8X"   // replace XYZ with your channel write API Key
void device_setup();
void device_loop();

#endif
