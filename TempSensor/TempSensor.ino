#include <TheThingsNetwork.h>
#include <Wire.h>

// Set your AppEUI and AppKey
const char *appEui = "0000000000000000";
const char *appKey = "6EA8568CA821F024293C5C4B06679A4E";
// App ID = isimavcvd
 
#define loraSerial Serial1
#define debugSerial Serial
 
// Replace REPLACE_ME with TTN_FP_EU868 or TTN_FP_US915
#define freqPlan TTN_FP_EU868
 
TheThingsNetwork ttn(loraSerial, debugSerial, freqPlan);
 
void setup()
{
  loraSerial.begin(57600);
  debugSerial.begin(9600);
    while (!debugSerial) {
    ;
    }

  debugSerial.println("-- STATUS");
  ttn.showStatus();
  debugSerial.println("-- JOIN");
  ttn.join(appEui, appKey);
}
 
void loop()
{
  int nDevices = 0;

  Serial.println("Scanning...");

  int adress = 16;
    Wire.beginTransmission(address);
    byte error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.print(address, HEX);
      Serial.println("  !");

      ++nDevices;
    } else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0) {
    Serial.println("No I2C devices found\n");
  } else {
    Serial.println("done\n");
  }
  
  debugSerial.println("-- LOOP");
    
  // Prepare array of 1 byte to indicate LED status
  byte data[1];
  data[0] = (digitalRead(LED_BUILTIN) == HIGH) ? 1 : 0;
      
  // Send it off
  ttn.sendBytes(data, sizeof(data));
        
  delay(10000);
}
