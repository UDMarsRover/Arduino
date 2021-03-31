#include <ros.h>
#include "HardwareSerial.h"
#include "MoogMotor.h"
#include <std_msgs/String.h>

int input;
float velocity = 1;
float acceleration = 1;
float positionM = 0;
boolean goodl = false;
boolean goodr = false;

ros::NodeHandle motor_node;
std_msgs::String command_out;
ros::Publisher commandOuttake("motor_control_out", &command_out);
MoogMotor leftDrive = MoogMotor(&Serial2); //Comms for left drive
MoogMotor rightDrive = MoogMotor(&Serial1); //Coms for right drive

void eBreak(){
  leftDrive.stop();
  rightDrive.stop();
  leftDrive.off();
  rightDrive.off();
  command_out.data = "Emergency Stop Message";
  commandOuttake.publish(&command_out);
}


void intake(std_msgs::String command_in){
  input = command_in.data; //Check for an input
    
    if(input == 'w'){
      goodl = leftDrive.setVelocity(velocity, acceleration);
      goodr = rightDrive.setVelocity(velocity, acceleration);

        if(goodl && goodr){command_out.data = command_in.data;}
        else{///error code////
        }
    }

    else if (input == 's'){
      goodl = leftDrive.setVelocity(-velocity,acceleration);
      goodr = rightDrive.setVelocity(-velocity,acceleration);
      
        if(goodl && goodr){command_out.data = command_in.data;}
        else{///error code////
        }
    }

    else if (input == 'd'){
      goodl = leftDrive.setVelocity(-velocity,acceleration);
      goodr = rightDrive.setVelocity(velocity,acceleration);
      
        if(goodl && goodr){command_out.data = command_in.data;}
        else{///error code////
        }
      }

    else if (input == 'a'){
      goodl = leftDrive.setVelocity(velocity,acceleration);
      goodr = rightDrive.setVelocity(-velocity,acceleration);
      
        if(goodl && goodr){command_out.data = command_in.data;}
        else{///error code////
        }
      }

    else if(input == 'e'){
      leftDrive.stop();
      rightDrive.stop();
      command_out.data = command_in.data;
    }

    else if (input == 'q'){
      leftDrive.setUp();
      rightDrive.setUp();
      command_out.data = command_in.data;
    }

    else if (input == 'p'){
      leftDrive.off();
      rightDrive.off();
      command_out.data = command_in.data;
    }

    else if (input == 'v'){
      eBreak();
    }

    else{
      command_out.data = "Unknown Command Code";
    }

    commandOuttake.publish(&command_out);
}



ros::Subscriber<std_msgs::String> commandIntake("motor_control_in", &intake);




void setup() {
  motor_node.initNode();
  motor_node.advertise(commandOuttake);

}

void loop() {
  motor_node.spinOnce();
}
