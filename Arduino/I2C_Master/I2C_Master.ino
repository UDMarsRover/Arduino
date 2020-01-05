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
  String returnData = getData(2);
  if (returnData.length()!=0){
    Serial.println(returnData);
    Serial.println("Got");
  }
  else{Serial.println("Data Return Error");}
}

void sendData(int slaveNumber, int command){
  Wire.beginTransmission(slaveNumber);
  Wire.write(command);
  Wire.endTransmission();
}

String getData(int slaveNumber){
  Serial.println("1");
  String dataIn = "";
  Serial.println("2");
  Wire.requestFrom(slaveNumber,26);
  Serial.println("3");
  while(0 < Wire.available()){
    Serial.println("4");
    char c = Wire.read();
    Serial.println("5");
    if (c != '?'){dataIn = dataIn+c;}
    Serial.println("6");
  }
  return dataIn;
  Serial.println("7");
}
