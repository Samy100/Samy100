#ifndef SLAVE_H
#define SLAVE_H
#include <Arduino.h>
#include <Wire.h>
#include <ArduinoBLE.h>
#include <Arduino_MKRENV.h>
#include <RTCZero.h>
#include <ArduinoLowPower.h>

void device_setup();
void device_loop();

#endif

