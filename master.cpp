/*
#include "master.h"
#include "common.h"
#include "common.h"


unsigned long previousMillis = 0; 
const long interval = 000; 
char ssid[] = WIFI_NAME;
char pass[] = WIFI_PASS;
int status = WL_IDLE_STATUS;

//ThingSpeak Stuff 
int keyIndex=0;
WiFiClient client;
//WiFiSSLClient client;
//WiFiEspClient  client;
unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;



struct Payload recv;
struct PayloadTime send;
RTCZero rtc;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 0);


void print2digits(int number) {
  if (number < 10) {
     Serial.print("0");
  }
  Serial.print(number);
}

void printTime() {
  Serial.print(rtc.getYear());
  Serial.print("-");
  print2digits(rtc.getMonth());
  Serial.print("-");
  print2digits(rtc.getDay());
  Serial.print(" ");

  print2digits(rtc.getHours());
  Serial.print(":");
  print2digits(rtc.getMinutes());
  Serial.print(":");
  print2digits(rtc.getSeconds());
  Serial.println(" UTC");
}

// connecting to Wi-Fi 
// void ConnectThingspeak(){
//   Serial.print("Attempting to connect to ThingSpeak now");
// }

void device_setup() {
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("starting WiFi failed!");
    while (1);
  }
  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }
  if(rtc.getEpoch() <= rtcMinTime) {
    Serial.print("Connecting to WiFi SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    while (status != WL_CONNECTED);
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);
    long rssi = WiFi.RSSI();
    Serial.print("Signal strength (RSSI):");
    Serial.println(rssi);
    
    timeClient.begin();
    timeClient.update();
    rtc.begin();
    rtc.setEpoch(timeClient.getEpochTime());

    WiFi.disconnect();
    WiFi.end();
  } else {
    rtc.begin();
    printTime();
  }

  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");
    while (1);
  }
  Serial.println("waiting for devices..");
  BLE.scanForUuid(BLE_UUID);
 // BLE.stopScan();//c need this ?
  previousMillis = millis();
  recv.hum = 0;
}


void connectSlave(BLEDevice peripheral) {
    Serial.print("Connecting.. ");
    if (peripheral.connect()) {
      Serial.println("ok");
    } else {
      Serial.println("fail");
      return;
    }

    // discover peripheral attributes
    Serial.print("Discovering attributes.. ");
    if (peripheral.discoverService(BLE_UUID)) {
      Serial.println("ok");
    }
    else {
      Serial.println("fail");
      peripheral.disconnect();
      return;
    }

  //Define character to read or write too    
  BLECharacteristic charact = peripheral.characteristic(CHR_UUID);


    if (!charact) { //c 
      Serial.println("Peripheral does not have required characteristic!");
      peripheral.disconnect();
      return;
    } else if (!charact.canRead()) {//c
      Serial.println("Peripheral does not have a readable characteristic!");
      peripheral.disconnect();
      return;
    }
    //charac data receiving sensor 1 data 

    charact.readValue(&recv, sizeof(struct Payload));
    Serial.print("ID: ");
    Serial.print(recv.devid);
    Serial.print(" Temp: ");
    Serial.print(recv.temp);
    Serial.print(" Hum: ");
    Serial.println(recv.hum);
    //print time and send epoch & payload  
    printTime();
    send.epoch = rtc.getEpoch();
    send.alarm = send.epoch + 60;
    charact.writeValue(&send, sizeof(struct PayloadTime));
    peripheral.disconnect();//c
   


  
}

//connecting to Wi-Fi 
// void conThingspeak(){
//     Serial.print("Attempting to connect to ThingSpeak now");

// }
void device_loop() {
  unsigned long currentMillis=millis(); 
  BLEDevice peripheral = BLE.available();

  if (peripheral) {
    Serial.print("Found ");
    Serial.print(peripheral.address());
    Serial.print(" '");
    Serial.print(peripheral.localName());
    Serial.print("' ");
    Serial.print(peripheral.advertisedServiceUuid());
    Serial.println();
    
    BLE.stopScan();
    connectSlave(peripheral);
    BLE.scanForUuid(BLE_UUID);// why scan again?
  }
  if (recv.hum > 0 && (currentMillis-previousMillis)> interval) {  //c
    previousMillis=currentMillis;
    BLE.stopScan();
    BLE.disconnect();
    BLE.end();
    delay(1000);  
    Serial.println("Ending BLE and uploading content");
    if(WiFi.status() != WL_CONNECTED){
      Serial.print("Attempting to connect to SSID: ");
      Serial.println(ssid);
      while(WiFi.status() != WL_CONNECTED){
        WiFi.begin(ssid, pass);
        Serial.print(".");
       delay(2000);     
      } 
    Serial.println("\nConnected.");
    }

    //set fields for 1st peripheral (slave 1) data
    ThingSpeak.begin(client);
    ThingSpeak.setField(1,recv.temp);
    ThingSpeak.setField(2,recv.hum);
    ThingSpeak.setField(3,recv.devid);

    int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    delay(2000);
  
    if(x == 200){
        Serial.println("Channel update successful.");
    }

    else {
        Serial.println("Problem updating channel. HTTP error code " + String(x));
    }

    recv.hum = 0;
    WiFi.disconnect();
    WiFi.end();
    BLE.begin();
    BLE.scanForUuid(BLE_UUID);

  }


}

*/
/**********************************************************************************Test 2 **********************************************************************************/ 
#include "master.h"
#include "common.h"
#include "common.h"
#include <WDTZero.h>

// WDTZero MyWatchDoggy; // Define WDT  
WDTZero MyWatchDoggy2; // Define WDT  

void myshutdown()
{
Serial.print("\nWe gonna shut down ! ..."); 
}


// unsigned long previousMillis = 0; 
// const long interval = 000; 
char ssid[] = WIFI_NAME;
char pass[] = WIFI_PASS;
int status = WL_IDLE_STATUS;

//ThingSpeak Stuff 
int keyIndex=0;
WiFiClient client;
unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;



struct Payload recv;
struct PayloadTime send;
RTCZero rtc;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 0);


void print2digits(int number) {
  if (number < 10) {
     Serial.print("0");
  }
  Serial.print(number);
}

void printTime() {
  Serial.print(rtc.getYear());
  Serial.print("-");
  print2digits(rtc.getMonth());
  Serial.print("-");
  print2digits(rtc.getDay());
  Serial.print(" ");

  print2digits(rtc.getHours());
  Serial.print(":");
  print2digits(rtc.getMinutes());
  Serial.print(":");
  print2digits(rtc.getSeconds());
  Serial.println(" UTC");
}

// connecting to Wi-Fi 
// void ConnectThingspeak(){
//   Serial.print("Attempting to connect to ThingSpeak now");
// }

void device_setup() {
  // if (WiFi.status() == WL_NO_MODULE) {
  //   Serial.println("starting WiFi failed!");
  //   while (1);
  // }
  // String fv = WiFi.firmwareVersion();
  // if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
  //   Serial.println("Please upgrade the firmware");
  // }
  // if(rtc.getEpoch() <= rtcMinTime) {
  //   Serial.print("Connecting to WiFi SSID: ");
  //   Serial.println(ssid);
  //   status = WiFi.begin(ssid, pass);
  //   while (status != WL_CONNECTED);
  //   IPAddress ip = WiFi.localIP();
  //   Serial.print("IP Address: ");
  //   Serial.println(ip);
  //   long rssi = WiFi.RSSI();
  //   Serial.print("Signal strength (RSSI):");
  //   Serial.println(rssi);
    
  //   timeClient.begin();
  //   timeClient.update();
  //   rtc.begin();
  //   rtc.setEpoch(timeClient.getEpochTime());

  //   WiFi.disconnect();
  //   WiFi.end();
  // } else {
    rtc.begin();
    // printTime();
  // }
 Serial.print("\nWDTZero-Demo : Setup Soft Watchdog at 32S interval"); 
//  MyWatchDoggy.attachShutdown(myshutdown);
//  MyWatchDoggy.setup(WDT_SOFTCYCLE32S);  // initialize WDT-softcounter refesh cycle on 32sec interval
 MyWatchDoggy2.attachShutdown(myshutdown);
 MyWatchDoggy2.setup(WDT_SOFTCYCLE16M);  // initialize WDT-softcounter refesh cycle on 17 mins interval
 	
  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");
    while (1);
  }
 // delay(5000);
  Serial.println("waiting for devices..");
  BLE.scanForUuid(BLE_UUID);
  // BLE.stopScan();//c need this ?
  // previousMillis = millis();
  //recv.hum = 0;
  // recv.devid=0; 

}


void connectSlave(BLEDevice peripheral) {
    Serial.print("Connecting.. ");
    if (peripheral.connect()) {
      Serial.println("ok");
    } else {
      Serial.println("fail");
      return;
    }

    // discover peripheral attributes
    Serial.print("Discovering attributes.. ");
    if (peripheral.discoverService(BLE_UUID)) {
      Serial.println("ok");
    }
    else {
      Serial.println("fail");
      peripheral.disconnect();
      return;
    }

  //Define character to read or write too    
  BLECharacteristic charact = peripheral.characteristic(CHR_UUID);


    if (!charact) { //c 
      Serial.println("Peripheral does not have required characteristic!");
      peripheral.disconnect();
      return;
    } else if (!charact.canRead()) {//c
      Serial.println("Peripheral does not have a readable characteristic!");
      peripheral.disconnect();
      return;
    }
    //charac data receiving sensor 1 data 

    charact.readValue(&recv, sizeof(struct Payload));
    Serial.print("ID: ");
    Serial.print(recv.devid);
    Serial.print("Vbat: ");
    Serial.print(recv.Vb);    
    Serial.print(" Temp: ");
    Serial.print(recv.temp);
    Serial.print(" Hum: ");
    Serial.println(recv.hum);
    //print time and send epoch & payload  
    printTime();
    send.epoch = rtc.getEpoch();
    send.alarm = send.epoch + 60;
    charact.writeValue(&send, sizeof(struct PayloadTime));
    peripheral.disconnect();//
  
}

void device_loop() {

  BLEDevice peripheral = BLE.available();
  if (peripheral) {
    Serial.print("Found ");
    Serial.print(peripheral.address());
    Serial.print(" '");
    Serial.print(peripheral.localName());
    Serial.print("' ");
    Serial.print(peripheral.advertisedServiceUuid());
    Serial.println();
    
    BLE.stopScan();
    connectSlave(peripheral);
    BLE.scanForUuid(BLE_UUID);// why scan again?
  }
  if (recv.hum > 0 ) {  //c
    BLE.stopScan();
    BLE.disconnect();
    BLE.end();
    delay(1000);  
    Serial.println("Ending BLE and uploading content");
      // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv != "1.0.0") {
    Serial.println("Please upgrade the firmware");
  }
    if(WiFi.status() != WL_CONNECTED){
      Serial.print("Attempting to connect to SSID: ");
      Serial.println(ssid);
      while(WiFi.status() != WL_CONNECTED){
        WiFi.begin(ssid, pass);
        Serial.print(".");
        delay(2000);     
      } 
    Serial.println("\nConnected.");


    } if (recv.devid==10){
      
    //set fields for 1st peripheral (slave 1) data
    ThingSpeak.begin(client);
    ThingSpeak.setField(1,recv.temp);
    ThingSpeak.setField(2,recv.hum);
    ThingSpeak.setField(6,recv.Vb);  

    } else if (recv.devid==20){
        //set fields for 1st peripheral (slave 1) data
    ThingSpeak.begin(client);  
    ThingSpeak.setField(3,recv.temp);
    ThingSpeak.setField(4,recv.hum);
    ThingSpeak.setField(7,recv.Vb);
    }
    ThingSpeak.setField(5,recv.devid);

    int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    delay(3000);
  
    if(x == 200){
        Serial.println("Channel update successful.");
    }

    else {
        Serial.println("Problem updating channel. HTTP error code " + String(x));
    }

    recv.hum = 0;
    recv.devid=0; 
    WiFi.disconnect();
    WiFi.end();
    BLE.begin();
    BLE.scanForUuid(BLE_UUID);
    MyWatchDoggy2.clear();  // refresh wdt 2- before it loops
  }

    // MyWatchDoggy.clear();  // refresh wdt - before it loops
 

}



/**********************************************************************************Test 3 **********************************************************************************/ 
/*
#include "master.h"
#include "common.h"



unsigned long previousMillis = 0; 
const long interval = 0; 
char ssid[] = WIFI_NAME;
char pass[] = WIFI_PASS;
int status = WL_IDLE_STATUS;

//ThingSpeak Stuff 
int keyIndex=0;
WiFiClient client;
//WiFiSSLClient client;
//WiFiEspClient  client;
unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

struct Payload recv;
struct Payload2 recv2;
struct PayloadTime send;
RTCZero rtc;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 0);

void print2digits(int number) {
  if (number < 10) {
     Serial.print("0");
  }
  Serial.print(number);
}

void printTime() {
  Serial.print(rtc.getYear());
  Serial.print("-");
  print2digits(rtc.getMonth());
  Serial.print("-");
  print2digits(rtc.getDay());
  Serial.print(" ");

  print2digits(rtc.getHours());
  Serial.print(":");
  print2digits(rtc.getMinutes());
  Serial.print(":");
  print2digits(rtc.getSeconds());
  Serial.println(" UTC");
}

void device_setup() {
  
  while (!Serial);
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("starting WiFi failed!");
    while (1);
  }
  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }
  if(rtc.getEpoch() <= rtcMinTime) {
    Serial.print("Connecting to WiFi SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    while (status != WL_CONNECTED);
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);
    long rssi = WiFi.RSSI();
    Serial.print("Signal strength (RSSI):");
    Serial.println(rssi);
    
    timeClient.begin();
    timeClient.update();
    rtc.begin();
    rtc.setEpoch(timeClient.getEpochTime());

    WiFi.disconnect();
    WiFi.end();
  } else {
    rtc.begin();
    printTime();
  }

  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");
    while (1);
  }
  Serial.println("waiting for devices..");
  BLE.scanForUuid(BLE_UUID);
  previousMillis = millis();
  recv.hum = 0;
  recv2.hum2 = 0;//c
  Serial.println("Completed scan..");
}

void connectSlave(BLEDevice peripheral) {
    Serial.print("Connecting.. ");
    if (peripheral.connect()) {
      Serial.println("ok1");
    } else {
      Serial.println("fail to connect to BLE_UUID");
      return;
    }

    // discover peripheral attributes
    Serial.print("Discovering attributes.. ");
    if (peripheral.discoverService(BLE_UUID)) {
      Serial.println("ok2");
    } else {
      Serial.println("fail ");
      peripheral.disconnect();
      return;
    }
    // else if (peripheral.discoverService(BLE_UUID2)) {//c
    //   Serial.println("ok");//c
    // }

  //Define character to read or write too   
  BLECharacteristic charact = peripheral.characteristic(CHR_UUID);
  BLECharacteristic charact2 = peripheral.characteristic(CHR_UUID2); //c

    if ((!charact)&&(!charact2)) { //c -if O cant read char1 and char 2
      Serial.println("Peripheral does not have required characteristic!");
      peripheral.disconnect();
      return;
    }else if ((!charact.canRead())&&(!charact2.canRead())) {//c
      Serial.println("Peripheral does not have a readable characteristic!");
      peripheral.disconnect();
      return;
    }
    // charac data receiving sensor 1 data
   if(charact){
    charact.readValue(&recv, sizeof(struct Payload));
    Serial.print("Temp: ");
    Serial.print(recv.temp);
    Serial.print(" Hum: ");
    Serial.println(recv.hum);
    // print time and send epoch & payload 
    printTime();
    send.epoch = rtc.getEpoch();
    send.alarm = send.epoch + 60;
    charact.writeValue(&send, sizeof(struct PayloadTime));
   }else if (charact2){//c 
    // charac2
    charact2.readValue(&recv2, sizeof(struct Payload2)); //c
    Serial.print("Temp: ");
    Serial.print(recv2.temp2);
    Serial.print(" Hum: ");
    Serial.println(recv2.hum2);
    // print time and send epoch & payload 
    printTime();
    send.epoch = rtc.getEpoch();
    send.alarm = send.epoch + 60;
    charact2.writeValue(&send, sizeof(struct PayloadTime));
   }

    peripheral.disconnect();//c
}

void device_loop() {

  unsigned long currentMillis=millis(); 
  BLEDevice peripheral = BLE.available();

//  if (! BLE.available()) {
//     Serial.println("not peripheral");
//     while (1);
//   }

  if (peripheral) {
    Serial.print("Found ");
    Serial.print(peripheral.address());
    Serial.print(" '");
    Serial.print(peripheral.localName());
    Serial.print("' ");
    Serial.print(peripheral.advertisedServiceUuid());
    Serial.println();
    
    BLE.stopScan();
    connectSlave(peripheral);
    BLE.scanForUuid(BLE_UUID);// why scan again?
    // BLE.scanForUuid(BLE_UUID2);//c
  } 
  // if ((recv.hum > 0 && (currentMillis-previousMillis)>interval )|| (recv2.hum2 > 0 && (currentMillis-previousMillis)> interval)) {  //c
 
   if(((recv2.hum2 > 0) ||(recv.hum > 0 )) && (currentMillis-previousMillis)> interval){  // cc set fields for 2nd peripheral (slave 2) data
   previousMillis=currentMillis;
    BLE.stopScan();
    BLE.disconnect();
    BLE.end();
    delay(1000);
    Serial.println("Ending BLE and uploading content");
    if(WiFi.status() != WL_CONNECTED){
      Serial.print("Attempting to connect to SSID: ");
      Serial.println(ssid);
      while(WiFi.status() != WL_CONNECTED){
        WiFi.begin(ssid, pass);
        Serial.print(".");
        delay(2000);     
      } 
      Serial.println("\nConnected.");
    }
    if(recv.hum>0){// if we receive data from first sensor
    ThingSpeak.begin(client);
    ThingSpeak.setField(1,recv.temp);
    ThingSpeak.setField(2,recv.hum);
    int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    delay(2000);
  
    if(x == 200){
        Serial.println("Channel update successful.");
    }
    else {
        Serial.println("Problem updating channel. HTTP error code " + String(x));
    }
    recv.hum = 0;
    WiFi.disconnect();
    WiFi.end();
    BLE.begin();
    BLE.scanForUuid(BLE_UUID);

    } else if(recv2.hum2>0){ // else if we receive data from second sensor
    ThingSpeak.begin(client);
    ThingSpeak.setField(3,recv2.temp2);
    ThingSpeak.setField(4,recv2.hum2);
    int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    delay(2000);
  
    if(x == 200){
        Serial.println("Channel update successful.");
    }
    else {
        Serial.println("Problem updating channel. HTTP error code " + String(x));
      }
    recv2.hum2 = 0;
    WiFi.disconnect();
    WiFi.end();
    BLE.begin();
    BLE.scanForUuid(BLE_UUID);      
    }


   }

  
    //set fields for 1st peripheral (slave 1) data
  // if (recv.hum > 0 && (currentMillis-previousMillis)> interval){
  //   ThingSpeak.begin(client);
  //   ThingSpeak.setField(1,recv.temp);
  //   ThingSpeak.setField(2,recv.hum);
    // }else if (recv2.hum2 > 0 && (currentMillis-previousMillis)> interval){  // cc set fields for 2nd peripheral (slave 2) data
    // ThingSpeak.setField(3,recv2.temp2);//c
    // ThingSpeak.setField(4,recv2.hum2);//c
    // }

    // int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    // delay(2000);
  
    // if(x == 200){
    //     Serial.println("Channel update successful.");
    // }
    // else {
    //     Serial.println("Problem updating channel. HTTP error code " + String(x));
    // }
    // BLE.stopScan();
    // BLE.scanForUuid(BLE_UUID2);
  

}
*/