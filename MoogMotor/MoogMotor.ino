#include "HardwareSerial.h"
#include <MoogMotor.h>
#include <ros.h>
#include <std_msgs/String.h>
MoogMotor motSF = MoogMotor(Serial);

ros::NodeHandle motorNode;                                                  //Create the node for this arduino
std_msgs::String inputCommand;                                              //Creae the type of input command for this node. (Always a HEX number represented as string)
ros::Publisher confirm("motor_control", &inputCommand);                     //Create the publisher to the motor_control topic


//This method takes in the command form ros, decides what to do with it, then returns it to the main node for confirmation
void intake(const std_msgs::String)
{
  String command;                                                           //local command variable
  command = inputCommand.data;                                              //Take in data form ROS
  MoogMotor::MotorMode motorMode;                                           //Create a motor mode variable
  float motorSpeed;                                                         //Create a motor speed varibale to upsate the system with
 
  //if not stop.....
    //Create an if structure based off of the command values and update variables
    motSF.driveMotor(motorMode, motorSpeed);
  //if stop
    motSF.slowToStop();


  //Return command once complete
  confirm.publish(&inputCommand);
}

ros::Subscriber<std_msgs::String> commandIntake("motor_contol", &intake);   //Create the subscriber to take in commands

void setup()
{
  //Set up ROS network
    motorNode.initNode(); 
    motorNode.advertise(confirm);
    motorNode.subscribe(commandIntake);
  //End ROS network setup
  
  motSF.initSerial();
  delay(1000);
}

void loop()
{
  motorNode.spinOnce();                                                     //check for updates in the topics once
  delay(100);                                                               //give a time delay in ms
}
