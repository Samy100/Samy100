/* Working WDT
#include "slave.h"
#include "common.h"
#include <WDTZero.h>

WDTZero MyWatchDoggy; // Define WDT  
void myshutdown()
{

Serial.print("\nWe gonna shut down ! ...");
  
}
void device_setup() {
  int t = 20; //Initialize serial and wait for port to open, max 10 seconds
  Serial.begin(9600);
  while (!Serial) {
    delay(500);
    if ( (t--) == 0 ) break;
  }  
 Serial.print("\nWDTZero-Demo : Setup Soft Watchdog at 32S interval"); 
 MyWatchDoggy.attachShutdown(myshutdown);
 MyWatchDoggy.setup(WDT_SOFTCYCLE32S);  // initialize WDT-softcounter refesh cycle on 32sec interval
}

void device_loop(){
  unsigned int t = 0;


  Serial.print("\nWatchdog Test1 - run 60 seconds with a WDT.clear()\n");
  for (t = 1; t < 60; ++t) {
    MyWatchDoggy.clear();  // refresh wdt - before it loops
    delay(950);
    Serial.print(t);Serial.print(".");
  }

  Serial.print("\n\nWatchdog Test2 - Free run wait for reset @32s\n");
  for (t = 1; t > 0; ++t) {
    delay(950);
    Serial.print(t);Serial.print(".");
    }
    
Serial.print("\nYou will never read this line");

}

*/

/* WDT (1)
#include "slave.h"
#include "common.h"

// Adafruit Watchdog Library Basic Usage Example
//
// Simple example of how to use the watchdog library.
//
// Author: Tony DiCola

#include <Adafruit_SleepyDog.h>

void setup() {
  Serial.begin(115200);
  while(!Serial) delay(10); 
  // wait for Arduino Serial Monitor (native USB boards)

  Serial.println("Adafruit Watchdog Library Demo!");
  Serial.println();

  // First a normal example of using the watchdog timer.
  // Enable the watchdog by calling Watchdog.enable() as below.
  // This will turn on the watchdog timer with a ~4 second timeout
  // before reseting the Arduino. The estimated actual milliseconds
  // before reset (in milliseconds) is returned.
  // Make sure to reset the watchdog before the countdown expires or
  // the Arduino will reset!
  int countdownMS = Watchdog.enable(4000);
  Serial.print("Enabled the watchdog with max countdown of ");
  Serial.print(countdownMS, DEC);
  Serial.println(" milliseconds!");
  Serial.println();

  // Now loop a few times and periodically reset the watchdog.
  Serial.println("Looping ten times while resetting the watchdog...");
  for(int i = 1; i <= 10; ++i) {
    Serial.print("Loop #"); Serial.println(i, DEC);
    delay(1000);
    // Reset watchdog with every loop to make sure the sketch keeps running.
    // If you comment out this call watch what happens in about 4 iterations!
    Watchdog.reset();
  }
  Serial.println();

  // Finally demonstrate the watchdog resetting by enabling it for a shorter
  // period of time and waiting a long time without a reset.  Notice you can
  // pass a _maximum_ countdown time (in milliseconds) to the enable call.
  // The library will try to use that value as the countdown, but it might
  // pick a smaller value if the hardware doesn't support it.  The actual
  // countdown value will be returned so you can see what it is.
  countdownMS = Watchdog.enable(4000);
  Serial.print("Get ready, the watchdog will reset in ");
  Serial.print(countdownMS, DEC);
  Serial.println(" milliseconds!");
  Serial.println();
  delay(countdownMS+1000);

  // Execution will never get here because the watchdog resets the Arduino!
}

void loop() {
  // We'll never actually get to the loop because the watchdog will reset in
  // the setup function.
  Serial.println("You shouldn't see this message.");
  delay(1000);
}
*/

/*
// First device (Slave 1)
#include "slave.h"
#include "common.h"


//Timing initialising
unsigned long previousMillis = 0; 
const long interval = 3000; 
// BLE Payload content 
struct Payload send;
struct PayloadTime recv;
RTCZero rtc;

BLEService comService(BLE_UUID);
BLECharacteristic payloadChar(CHR_UUID, BLERead | BLEWrite, sizeof(struct Payload));


// int RX=13; 

void updatePayload() {
    send.devid = 10;
    send.temp = ENV.readTemperature();
    send.hum = ENV.readHumidity();
    Serial.print("Temp: ");
    Serial.print(send.temp);
    Serial.print(" Hum: ");
    Serial.println(send.hum);
}

void print2digits(int number) {
  if (number < 10) {
    Serial.print("0");
  }
  Serial.print(number);
}

void charWritten(BLEDevice central, BLECharacteristic ch) {
    ch.readValue(&recv, sizeof(struct PayloadTime));
    if(recv.epoch > rtcMinTime) rtc.setEpoch(recv.epoch);
    if(recv.alarm > rtcMinTime) {
        rtc.setAlarmEpoch(recv.alarm);
        //rtc.enableAlarm(rtc.MATCH_YYMMDDHHMMSS);
        //rtc.attachInterrupt(device_setup);
        int stime =  (recv.alarm -recv.epoch)*100;
                      // delay(500);//p

    
        // Serial.print(F("Disconnected from central: "));
        Serial.print("Sleeping for: 6 seconds  ");
         Serial.println(stime);

        /// Serial.println(central.address());  
       // LowPower.sleep(stime);
        //Serial.print("awake now \n "); 
        // device_loop();   
       // central.disconnect();
       // delay(500);
        //BLE.stopAdvertise();
        // BLE.end();
        // rtc.standbyMode();
        

    }
}

void device_setup() {
  // pinMode(RX,13);
  Serial.begin(9600);
  //while (!Serial);

  if (!ENV.begin()) {
    Serial.println("Failed to initialize MKR ENV shield!");
    while (1);
  }
  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");
    while (1);
  }
  rtc.begin();
 // set advertised local name and service UUID:
  BLE.setLocalName("LED");
  BLE.setAdvertisedService(comService);
  comService.addCharacteristic(payloadChar);
  BLE.addService(comService);

 // updatePayload();
//   BLE.advertise();
}

void device_loop() {

  unsigned long currentMillis=millis(); 
  payloadChar.setEventHandler(BLEWritten, charWritten);
  BLE.advertise();
  BLEDevice central = BLE.central();
 // delay(500); //p
  if (central.connected()) {
    Serial.println("Connected to central: ");
    Serial.println(central.address());
    updatePayload();
    // delay(800);
    payloadChar.writeValue(&send, sizeof(struct Payload));
  } 
  if ((currentMillis-previousMillis) > interval || (recv.epoch > rtcMinTime)) {  
    previousMillis=currentMillis;
    recv.epoch = rtcMinTime; 
        central.disconnect();
        //delay(500);//p
        BLE.stopAdvertise();
        LowPower.deepSleep(9000);
        Serial.print("awake now \n "); 
        // device_loop();   

        // BLE.end();
  }
  
}
// /dev/tty_4B2A94 
// /dev/tty_1A88FD

*/


/******************************************************************************** Second Device (Slave 2) *********************************************************************/


// First device (Slave 1)
#include "slave.h"
#include "common.h"


//Timing initialising
unsigned long previousMillis = 0; 
const long interval = 3000; //10min=600,000
// BLE Payload content 
struct Payload send;
struct PayloadTime recv;
RTCZero rtc;

BLEService comService(BLE_UUID);
BLECharacteristic payloadChar(CHR_UUID, BLERead | BLEWrite, sizeof(struct Payload));


// int RX=13; 

void updatePayload() {
   
    send.temp = ENV.readTemperature();
    send.hum = ENV.readHumidity();
    send.devid = 20; //prev =10
    float A=analogRead(ADC_BATTERY);
    send.Vb=(A* (4 / 1023.0));
    // Serial.print("Temp: ");
    //Serial.print(send.temp);
    // Serial.print(" Hum: ");
    //Serial.println(send.hum);
}


void charWritten(BLEDevice central, BLECharacteristic ch) {
    ch.readValue(&recv, sizeof(struct PayloadTime));
    if(recv.epoch > rtcMinTime) rtc.setEpoch(recv.epoch);
    if(recv.alarm > rtcMinTime) {
        rtc.setAlarmEpoch(recv.alarm);
        //rtc.enableAlarm(rtc.MATCH_YYMMDDHHMMSS);
        //rtc.attachInterrupt(device_setup);
        // int stime =  (recv.alarm -recv.epoch)*100;
                      // delay(500);//p

    
        // Serial.print(F("Disconnected from central: "));
        // Serial.print("Sleeping for: 6 seconds  ");
        //  Serial.println(stime);

        /// Serial.println(central.address());  
       // LowPower.sleep(stime);
        //Serial.print("awake now \n "); 
        // device_loop();   
       // central.disconnect();
       // delay(500);
        //BLE.stopAdvertise();
        // BLE.end();
        // rtc.standbyMode();
        

    }
}



void device_setup() {
  // pinMode(RX,13);
  Serial.begin(9600);
  //while (!Serial);

  if (!ENV.begin()) {
    // Serial.println("Failed to initialize MKR ENV shield!");
    while (1);
  }
  if (!BLE.begin()) {
    // Serial.println("starting BLE failed!");
    while (1);
  }
  rtc.begin();
 // set advertised local name and service UUID:
  BLE.setLocalName("LED");
  BLE.setAdvertisedService(comService);
  comService.addCharacteristic(payloadChar);
  BLE.addService(comService);

 // updatePayload();
//   BLE.advertise();
}



void device_loop() {

  unsigned long currentMillis=millis(); 
  payloadChar.setEventHandler(BLEWritten, charWritten);
  BLE.advertise();
  BLEDevice central = BLE.central();
 // delay(500); //p
  if (central.connected()) {
    // Serial.println("Connected to central: ");
    Serial.println(central.address());
    updatePayload();
    // delay(800);
    payloadChar.writeValue(&send, sizeof(struct Payload));
    
  } 
  if ((currentMillis-previousMillis) > interval || (recv.epoch > rtcMinTime)) {  
    previousMillis=currentMillis;
    recv.epoch = rtcMinTime; 
        central.disconnect();
        //delay(500);//p
        BLE.stopAdvertise();
        BLE.end(); 
        LowPower.deepSleep(300000);

        BLE.begin();
        BLE.setLocalName("LED");
        BLE.setAdvertisedService(comService);
        comService.addCharacteristic(payloadChar);
        BLE.addService(comService);
              
        // Serial.print("awake now \n "); 
        // device_loop();   

        // BLE.end();
  }
  
  
}
// /dev/tty_4B2A94 
// /dev/tty_1A88FD











/******************************************************************************** 3rd Device (Slave 3) *********************************************************************/
/*
#include "slave.h"
#include "common.h"



// Timing initialising
unsigned long previousMillis = 0; 
const long interval = 3000; 
// BLE Payload content 
struct Payload2 send;
struct PayloadTime recv;
RTCZero rtc;

BLEService comService(BLE_UUID);
BLECharacteristic payloadChar(CHR_UUID2, BLERead | BLEWrite, sizeof(struct Payload2));


// int RX=13; 

void updatePayload() {
    send.temp2 = ENV.readTemperature();
    send.hum2 = ENV.readHumidity();
    Serial.print("Temp2: ");
    Serial.print(send.temp2);
    Serial.print(" Hum2: ");
    Serial.println(send.hum2);
}

void print2digits(int number) {
  if (number < 10) {
    Serial.print("0");
  }
  Serial.print(number);
}

void charWritten(BLEDevice central, BLECharacteristic ch) {
    ch.readValue(&recv, sizeof(struct PayloadTime));
    if(recv.epoch > rtcMinTime) rtc.setEpoch(recv.epoch);
    if(recv.alarm > rtcMinTime) {
        rtc.setAlarmEpoch(recv.alarm);
        //rtc.enableAlarm(rtc.MATCH_YYMMDDHHMMSS);
        //rtc.attachInterrupt(device_setup);
        int stime =  (recv.alarm -recv.epoch)*100;
                      delay(500);

    
        // Serial.print(F("Disconnected from central: "));
       Serial.print("Sleeping for: 6 seconds  ");
         Serial.println(stime);

        /// Serial.println(central.address());  
       // LowPower.sleep(stime);
        //Serial.print("awake now \n "); 
        // device_loop();   
       // central.disconnect();
       // delay(500);
        //BLE.stopAdvertise();
        // BLE.end();
        // rtc.standbyMode();
        

    }
}

void device_setup() {
  // pinMode(RX,13);
  Serial.begin(9600);
  // while (!Serial);

  if (!ENV.begin()) {
    Serial.println("Failed to initialize MKR ENV shield!");
    while (1);
  }
  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");
    while (1);
  }
  rtc.begin();
 // set advertised local name and service UUID:
  BLE.setLocalName("LED");
  BLE.setAdvertisedService(comService);
  comService.addCharacteristic(payloadChar);
  BLE.addService(comService);

 // updatePayload();
//   BLE.advertise();
}

void device_loop() {

  unsigned long currentMillis=millis(); 
  payloadChar.setEventHandler(BLEWritten, charWritten);
  BLE.advertise();
  BLEDevice central = BLE.central();
  //delay(500);
  if (central.connected()) {
    Serial.println("Connected to central: ");
    Serial.println(central.address());
    updatePayload();
    payloadChar.writeValue(&send, sizeof(struct Payload2));
  //  delay(500);
  } 
  if ((currentMillis-previousMillis) > interval || (recv.epoch > rtcMinTime)) {  
    previousMillis=currentMillis;
    recv.epoch = rtcMinTime; 
        central.disconnect();    
        // delay(500);    
        BLE.stopAdvertise();
        Serial.println("Sleeping for 6 minutes");
        LowPower.deepSleep(6000);
        Serial.print("awake now \n "); 
        // device_loop();   

        // BLE.end();
  }
  
}
// /dev/tty_4B2A94 
// /dev/tty_1A88FD
*/
