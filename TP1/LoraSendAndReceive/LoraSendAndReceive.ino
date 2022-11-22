/*
  Lora Send And Receive
  This sketch demonstrates how to send and receive data with the MKR WAN 1300/1310 LoRa module.
  This example code is in the public domain.
*/

#include <MKRWAN.h>
#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_SHT31.h"

bool enableHeater = false;
uint8_t loopCnt = 0;

// 8248E25F4C09C294AD25ABDBA50343DC
const char Crypt[] = {0x82, 0x48, 0xE2, 0x5F, 0x4C, 0x09, 0xC2, 0x94, 0xAD, 0x25, 0xAB, 0xDB, 0xA5, 0x03, 0x43, 0xDC};

Adafruit_SHT31 sht31 = Adafruit_SHT31();

LoRaModem modem;

// Uncomment if using the Murata chip as a module
// LoRaModem modem(Serial1);

#include "arduino_secrets.h"

String Binary_to_String(char * tab, int _size){
  String chaine = "";
  for(int i = 0; i<_size; ++i){
    char temp[2];
    sprintf(temp, "%02X", tab[i]);
    chaine += temp; 
  }
  chaine.toUpperCase();
  return chaine;
}

void XorOp(char * S1, const char * S2, const int _size){
  for(int i = 0; i< _size; ++i){
    S1[i] = S1[i] ^ S2[i];
    
  }
  //Serial.println(S1);
}

// Please enter your sensitive data in the Secret tab or arduino_secrets.h

char key[] = SECRET_APP_KEY;
String appEui = SECRET_APP_EUI;
String appKey;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  SerialLoRa.begin(19200);
  XorOp(key, Crypt, 16);
  appKey = Binary_to_String(key, 16);
  while (!Serial)
    delay(10);     // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Please input your AppKey :");
  while(Serial.available() == 0);
  String chaine = Serial.readString();

  while(!chaine.equals(appKey + "\r\n")){
    Serial.println("\nWrong App Key");
    Serial.println("input : " + chaine + "appKey : " + appKey);
    Serial.println("Please input your AppKey :");
    while(Serial.available() == 0);
    chaine = Serial.readString();
  }
  //Serial.println(appKey);
  while(!SerialLoRa)
    delay(10);
  Serial.println("boot to start module");

  for(int i=0; i<appKey.length(); ++i){
    SerialLoRa.write("AT$NVM " + i + key[i]);
  }
  

  // change this to your regional band (eg. US915, AS923, ...)
  if (!modem.begin(EU868)) { 
    Serial.println("Failed to start module");
    while (1) {}
  };
  Serial.print("Your module version is: ");
  Serial.println(modem.version());
  Serial.print("Your device EUI is: ");
  Serial.println(modem.deviceEUI());
  
  int connected = modem.joinOTAA(appEui, appKey);
  
  if (!connected) {
    Serial.println("Something went wrong; are you indoor? Move near a window and retry");
    while (1) {}
  }
  
  // Set poll interval to 60 secs.
  //modem.minPollInterval(60);
  modem.dataRate(3);
  //delay(100);
  
  // NOTE: independent of this setting, the modem will
  // not allow sending more than one message every 2 minutes,
  // this is enforced by firmware and can not be changed.
}

void loop() {
  if(Serial.available() > 0){
    char c = Serial.read();
    SerialLoRa.print(c);
  }
  if(SerialLoRa.available() > 0){
    char c = SerialLoRa.read();
    Serial.print(c);
  }

  /*
  float t = sht31.readTemperature();
  float h = sht31.readHumidity();

  if (! isnan(t)) {  // check if 'is not a number'
    Serial.print("Temp *C = "); Serial.print(t); Serial.print("\t\t");
  } else { 
    Serial.println("Failed to read temperature");
  }
  
  if (! isnan(h)) {  // check if 'is not a number'
    Serial.print("Hum. % = "); Serial.println(h);
  } else { 
    Serial.println("Failed to read humidity");
  }
  
  String msg = Serial.readStringUntil('\n');
  //String msg = String(32);//String(t,2);

  Serial.println();
  Serial.print("Sending: " + msg + " - ");
  for (unsigned int i = 0; i < msg.length(); i++) {
    Serial.print(msg[i] >> 4, HEX);
    Serial.print(msg[i] & 0xF, HEX);
    Serial.print(" ");
  }
  Serial.println();

  int err = 0;
  /*
  modem.beginPacket();
  modem.print(msg);
  err = modem.endPacket(true);
  
  if (err > 0) {
    Serial.println("Message sent correctly!");
  } else {
    Serial.println("Error sending message :(");
    Serial.println("(you may send a limited amount of messages per minute, depending on the signal strength");
    Serial.println("it may vary from 1 message every couple of seconds to 1 message every minute)");
  }
  delay(20000);
  if (!modem.available()) {
    Serial.println("No downlink message received at this time.");
    return;
  }
  char rcv[64];
  int i = 0;
  while (modem.available()) {
    rcv[i++] = (char)modem.read();
  }
  Serial.print("Received: ");
  for (unsigned int j = 0; j < i; j++) {
    Serial.print(rcv[j] >> 4, HEX);
    Serial.print(rcv[j] & 0xF, HEX);
    Serial.print(" ");
  }
  Serial.println();
  */
}
