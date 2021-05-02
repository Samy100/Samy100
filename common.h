#ifndef COMMON_H
#define COMMON_H


#include <Arduino.h>

struct Payload {
  uint8_t devid;
  float temp;
  float hum;
  float Vb; 
  // float press;//c
} payload;

//payload of second device (slave 2)
// struct Payload2 {

//   float temp2;
//   float hum2;//c
//  // float press;//c
// } payload2;

//both samme payloadtime
struct PayloadTime {
  uint32_t epoch;
  uint32_t alarm;
} payloadTime;

// Default time of RTC when board is reset
uint32_t rtcMinTime = 943920000;
/*First Device UUID and Characteristics*/ 
char BLE_UUID[] = "19b10000-e8f2-537e-4f6c-d104768a1214";
char CHR_UUID[] = "19b10000-e8f2-537e-4f6c-d104768a1215";

/*Second Device UUID and Characteristics*/
//char BLE_UUID2[] = "19b10000-e8f2-537e-4f6c-d204768a1216";//c
//char CHR_UUID2[] = "19b10000-e8f2-537e-4f6c-d104768a1210";//c

#endif


/* device power 

// void device_setup() {
//   pinMode(LED_BUILTIN, OUTPUT);
//   // Uncomment this function if you wish to attach function dummy when RTC wakes up the chip
//   // LowPower.attachInterruptWakeup(RTC_ALARM_WAKEUP, dummy, CHANGE);
// }

// void device_loop() {
//   digitalWrite(LED_BUILTIN, HIGH);
//   delay(500);
//   digitalWrite(LED_BUILTIN, LOW);
//   delay(500);
//   // Triggers a 2000 ms sleep (the device will be woken up only by the registered wakeup sources and by internal RTC)
//   // The power consumption of the chip will drop consistently
//   LowPower.sleep(3000);
// }

// void dummy() {
//   // This function will be called once on device wakeup
//   // You can do some little operations here (like changing variables which will be used in the loop)
//   // Remember to avoid calling delay() and long running functions since this functions executes in interrupt context
// }
 */
