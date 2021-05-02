#include <Arduino.h>
#include <ArduinoBLE.h>
#include <WiFiNINA.h>
#include <NTPClient.h>


#if DEVICE == MASTER
  #include "master.h"
#else
  #include "slave.h"
#endif

#define xstr(s) str(s)
#define str(s) #s

void setup() {
  Serial.begin(9600);
  // while (!Serial);
  Serial.println(str(DEVICE) "=" xstr(DEVICE));
  device_setup();
}

void loop() {
  device_loop();
}
