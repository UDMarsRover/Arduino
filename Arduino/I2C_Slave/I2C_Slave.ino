#include <Wire.h>

char data[120];
int command;
boolean setUp = false;

void setup() {
  // put your setup code here, to run once:
  Wire.begin(0x04);
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
   byte dataIn = Wire.read();
   if(dataIn!=0){command=dataIn;}
   if (command == 0x40){
    setUp=true;
   }
   Serial.println(command);
}

void sendHandler(){
  if (setUp && command == 0x40){
    Wire.write(0x40);
    setUp = false;
  }
  else{
    if (command==0){/*do nothing, this is a message end command by the RPi. This can not be used.*/}
    if (command==1){Wire.print("[You got command 1]");}
    else{Wire.print("[Unkown Command]");}
  }

}
