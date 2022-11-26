#include <MKRWAN.h>
#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_SHT31.h"
#include "arduino_secrets.h"

/*******************
* Global variables *
********************/
bool enableHeater = false;
uint8_t loopCnt = 0;
//8248E25F4C09C294AD25ABDBA50343DC
const char Crypt[] = {0x82, 0x48, 0xE2, 0x5F, 0x4C, 0x09, 0xC2, 0x94, 0xAD, 0x25, 0xAB, 0xDB, 0xA5, 0x03, 0x43, 0xDC};
Adafruit_SHT31 sht31 = Adafruit_SHT31();
LoRaModem modem;
char key[] = SECRET_APP_KEY;
String appEui = SECRET_APP_EUI;
String appKey;

/******************************************************************************************
* Function : Binary_to_String                                                             *
*                                                                                         *
* param : Char *, int                                                                     *
*                                                                                         *
* Execution : Convert a char array of Hexadecimal into their ASCII equivalent in a String *
*******************************************************************************************/
String Binary_to_String(char * tab, const int _size){
  String chaine = "";
  for(int i = 0; i<_size; ++i){
    char temp[2];
    sprintf(temp, "%02X", tab[i]);
    chaine += temp;
  }
  chaine.toUpperCase();
  return chaine;
}

/********************************************************
* Function : XorOp                                      *
*                                                       *
* param : Char *, const char *, const int               *
*                                                       *
* Execution : Do a XOR operation between two char array *
*********************************************************/
void XorOp(char * S1, const char * S2, const int _size){
  for(int i = 0; i< _size; ++i){
    S1[i] = S1[i] ^ S2[i];
  }
}

void setup() {
  /*******************************
  * Init of Serial communication *
  ********************************/
  Serial.begin(115200);
  SerialLoRa.begin(19200);
  while (!Serial)
    delay(10);     // will pause Zero, Leonardo, etc until serial console opens
  while(!SerialLoRa)
    delay(10);

  /*********************
  * Decrypting the key *
  **********************/
  XorOp(key, Crypt, 16);
  appKey = Binary_to_String(key, 16);
  
  /********************************************
  * Waiting for user to input Application key *
  *********************************************/
  Serial.println("Please input your AppKey :");
  while(Serial.available() == 0);
  String chaine = Serial.readString();

  while(!chaine.equals(appKey + "\r\n")){
    Serial.println("\nWrong App Key");
    Serial.println("Please input your AppKey :");
    while(Serial.available() == 0);
    chaine = Serial.readString();
  }

  /*******************************************
  * Starting modem with Europe configuration *
  ********************************************/
  Serial.println("boot to start module");
  // change this to your regional band (eg. US915, AS923, ...)
  if (!modem.begin(EU868)) {
    Serial.println("Failed to start module");
    while (1) {}
  };
  Serial.print("Your module version is: ");
  Serial.println(modem.version());
  Serial.print("Your device EUI is: ");
  Serial.println(modem.deviceEUI());

  /*****************************************************
  * Starting to write Application key inside the modem *
  ******************************************************/
  for(int i=0; i<appKey.length(); ++i){
    SerialLoRa.write("AT$NVM " + i + key[i]);
  }

  /**********************************************************
  * Connecting the modem to a LoRaWAN network (like Helium) *
  ***********************************************************/
  int connected = modem.joinOTAA(appEui, appKey);
  if (!connected) {
    Serial.println("Something went wrong; are you indoor? Move near a window and retry");
    while (1) {}
  }

  modem.dataRate(3);
}

void loop() {
  /************************************************************************
  * Testing part                                                          *
  *                                                                       *
  * Used to communicate directly with the modem using Arduino ide monitor *
  *************************************************************************/
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
