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
Adafruit_SHT31 sht31 = Adafruit_SHT31();
LoRaModem modem;
String appEui = SECRET_APP_EUI;
String appKey;

void setup() {
  /*******************************
  * Init of Serial communication *
  ********************************/
  Serial.begin(19200);
  SerialLoRa.begin(19200);
  while (!Serial)
    delay(10);     // will pause Zero, Leonardo, etc until serial console opens
  while(!SerialLoRa)
    delay(10);
  
  /********************************************************
  * Looking in the nvm if the user already inserted a key *
  *********************************************************/
  String command = "AT$NVM 0\r\n";
  SerialLoRa.print(command);
  while(SerialLoRa.available() == 0);
  String lorastr = SerialLoRa.readString();
  

  if(lorastr[4] != '1'){
    /********************************************
    * Waiting for user to input Application key *
    *********************************************/
    Serial.println("Please input your AppKey :");
    while(Serial.available() == 0);
    String chaine = Serial.readString();

    /*******************************************************************
    * Changing the flag so it won't ask another time to insert the key *
    ********************************************************************/
    command = "AT$NVM 0,1\r\n";
    Serial.println(command);
    SerialLoRa.print(command);
    
    /***********************************
    * Writing the app key into the nvm *
    ************************************/
    for(int i=0; i<chaine.length() ; ++i){
      command = "AT$NVM " + String(i+1) + "," + String((int)chaine[i]) + "\r\n";
      Serial.println(command);
      SerialLoRa.print(command);
    }

    /**************************************************
    * Writing a char $ to mark the end of the app key *
    ***************************************************/
    command = "AT$NVM " + String(chaine.length()+1) + "," + String((int)'$') + "\r\n";
    Serial.println(command);
    SerialLoRa.print(command);
  }

  
  int ind = 0;
  while(lorastr.substring(4,6).toInt() != (int)'$'){
    /**************************************
    * Retrieving the app key from the nvm *
    ***************************************/
    command = "AT$NVM " + String(ind) + "\r\n";
    Serial.println(command);
    SerialLoRa.print(command);
    while(SerialLoRa.available() == 0);
    lorastr = SerialLoRa.readString();

    /**********************************************************
    * Parsing only the important part of LoRa returned string *
    ***********************************************************/
    Serial.println(lorastr.substring(4,6));
    Serial.println((char)lorastr.substring(4,6).toInt());
    appKey += (char)lorastr.substring(4,6).toInt();
    ++ind;
  }
  
  /************************************************************************
  * Removing the first and last character of nvm (flag and end of appkey) *
  *************************************************************************/
  Serial.println(appKey.substring(1,appKey.length()-1));
  Serial.println("6EA8568CA821F024293C5C4B06679A4E");
  
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

  /********************************************
  * Blocking Application key inside the modem *
  *********************************************/
  command = "AT$APKACCESS\r\n";
  SerialLoRa.print(command);

  /**********************************************************
  * Connecting the modem to a LoRaWAN network (like Helium) *
  ***********************************************************/
  /*
  int connected = modem.joinOTAA(appEui, appKey);
  if (!connected) {
    Serial.println("Something went wrong; are you indoor? Move near a window and retry");
    while (1) {}
  }*/

  /***************************************************
  * Setting modem rate to send data every 15 seconds *
  ****************************************************/
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
  */
  /*
  //String msg = Serial.readStringUntil('\n');
  String msg = String(32);//String(t,2);

  Serial.println();
  Serial.print("Sending: " + msg + " - ");
  for (unsigned int i = 0; i < msg.length(); i++) {
    Serial.print(msg[i] >> 4, HEX);
    Serial.print(msg[i] & 0xF, HEX);
    Serial.print(" ");
  }
  Serial.println();

  int err = 0;
  
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
