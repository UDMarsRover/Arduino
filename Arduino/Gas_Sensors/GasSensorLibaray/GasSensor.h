/*
 * GasSensor.h - header file for UDMRT Gas Sensor Libary Setup
 * Created by Greg Molskow on March 27, 2020
 */

#ifndef GasSensor_h
#define GasSensor_h

#include "Arduino.h"

class GasSensor{

  public:
    GasSensor(int analogPin, int digitalPin, int RL_Value);
    float *getData();
    void sensorCalibration();


  
  private:
    int __aPin__;
    int __dPin__;
    float __Ro__;
    float sensorValueCalculation();
    float __RL_Value__;
    float sensorValue;
    float sensorRawValue;
    float voltage;
    float gasValue;
    float gasRatio;
    int digitalInput;
    float *returnArray;
};

#endif
