#include <Wire.h>



void setup() {
  // put your setup code here, to run once:
  Wire.begin(1);
  Serial.begin(9600);
  Serial.write("Setup Complete\n");
  
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Sending Data");
  sendData(2,0);
  Serial.println("Sent");
  Serial.println("Gettign Data");
  getData(2);
  Serial.println("Got");
  delay(2000);
  
}

void sendData(int slaveNumber, int command){
  Wire.beginTransmission(slaveNumber);
  Wire.write(command);
  Wire.endTransmission();
}

void getData(int slaveNumber){
  String dataIn = "";
  char dataArray[120];
  int i=0;
  Wire.requestFrom(slaveNumber,26);
  while(0 < Wire.available()){
    char c = Wire.read();
    Serial.print(c);
    dataArray[i] = c;
    i++;
  }
}
