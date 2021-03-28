#include "HardwareSerial.h"
#include "MoogMotor.h"


int input;
float velocity = 1;
float acceleration = 1;
float positionM = 0;
boolean goodl = false;
boolean goodr = false;

MoogMotor leftDrive = MoogMotor(&Serial2); //Comms for left drive
MoogMotor rightDrive = MoogMotor(&Serial1); //Coms for right drive

void setup() {

  Serial.begin(9600); //Start a serial to take in keyboard commands

}

void loop() {

  if(Serial.available()){
    
    input = Serial.read(); //Check for an input
    
    if(input == 'w'){
      goodl = leftDrive.setVelocity(velocity, acceleration);
      goodr = rightDrive.setVelocity(velocity, acceleration);

      if(goodl && goodr){
        Serial.println("Running Forward");
        positionM = positionM + 0.1;
        }
      
    }

    else if (input == 's'){
      goodl = leftDrive.setVelocity(-velocity,acceleration);
      goodr = rightDrive.setVelocity(-velocity,acceleration);
      if(goodl && goodr){Serial.println("Running Backwards");}
    }

    else if (input == 'd'){
      goodl = leftDrive.setVelocity(-velocity,acceleration);
      goodr = rightDrive.setVelocity(velocity,acceleration);
      if(goodl && goodr){Serial.println("Running Backwards");}
    }

    else if (input == 'a'){
      goodl = leftDrive.setVelocity(velocity,acceleration);
      goodr = rightDrive.setVelocity(-velocity,acceleration);
      if(goodl && goodr){Serial.println("Running Backwards");}
    }

    else if(input == 'e'){
      leftDrive.stop();
      rightDrive.stop();
      Serial.println("Stopped");
    }

    else if (input == 'q'){
      leftDrive.setUp();
      rightDrive.setUp();
      Serial.println("Startup...");
    }

    else if (input == 'p'){
      leftDrive.off();
      rightDrive.off();
      Serial.println("Shutdown..");
    }
    
  }
}
