/*
 * MoogMotor.cpp - Library for controlling Moog Smart Motors via HardwareSerial.
 * Created by Joe Ditz on Jan 27, 2021
 */

#include "Arduino.h"
#include "HardwareSerial.h"
#include "MoogMotor.h"

MoogMotor::MoogMotor(HardwareSerial associatedSerial)
{
  serial = &associatedSerial;
  //initSerial();
}

boolean MoogMotor::driveMotor(MotorMode operationMode, float value)
{
  if(abs(value) <= 1)
  {
    if(mode != operationMode)
    {
      switch(operationMode)
      {
        case POS:
          serial->print("MP \r");
          break;
        case VEL:
          serial->print("MV \r");
          break;
        case TOR:
          serial->print("MT \r");
          break;
      }
      mode = operationMode;
     }

    value = int(value * 32767.0); //T can be -32767 through 32767
    serial->print("T=");
    serial->print(value);
    serial->print(" \r");
    
    serial->print("G \r");
    
    delay(1);
    return true;
  }
  return false;
}

void MoogMotor::hault()
{
  serial->print("S \r");
}

void MoogMotor::slowToStop()
{
  serial->print("X \r");
}

void MoogMotor::initSerial()
{
  serial->begin(9600);
  serial->print("MDE \r");
  delay(200);
  serial->print("EIGN(2) \r");
  delay(200);
  serial->print("EIGN(3) \r");
  delay(200);
  serial->print("ZS \r");
  delay(200);
}
