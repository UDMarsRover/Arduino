#include <Wire.h>

char data[120];
int command;

void setup() {
  // put your setup code here, to run once:
  Wire.begin(2);
  Serial.begin(9600);
  Wire.onReceive(receiveHandler);
  Wire.onRequest(sendHandler);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);
  Serial.write("Waiting\n");
}

void receiveHandler(int dataLength){
   command = (int)Wire.read();
}

void sendHandler(){
  String returnPackage;
  if(command==0){
    returnPackage = "Code 0 has been registered";
  }
  for(int i=0; i<sizeof(returnPackage); i++){
    char c = returnPackage.charAt(i);
    Wire.write(c);
   }
  
}
