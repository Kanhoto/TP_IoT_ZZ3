void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  SerialLoRa.begin(19200);

  while (!Serial)
    delay(10);     // will pause Zero, Leonardo, etc until serial console opens
  while(!SerialLoRa)
    delay(10);
}

void HextoDec(char[] inputHex, int _size){
  for(int i=0; i<_size; i+=2){
    
  }
}
void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0){
    char c = Serial.read();
    SerialLoRa.print(c);
  }
  if(SerialLoRa.available() > 0){
    char c = SerialLoRa.read();
    Serial.print(c);
  }
}
