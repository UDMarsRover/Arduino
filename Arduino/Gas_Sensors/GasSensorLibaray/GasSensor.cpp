/*
 GasSensor.cpp - .cpp file for the UDMRT GasSensor library
 Created by Greg Molskow on March 27, 2020
*/

#include "Arduino.h"
#include "GasSensor.h"


GasSensor::GasSensor(int analogPin, int digitalPin, int RL_Value){
    __aPin__ = analogPin;
    __dPin__ = digitalPin;
    __RL_Value__ = RL_Value;
    returnArray = new float[3];
}


void GasSensor::sensorCalibration(){
    /*
    This function gets the base reading for the sensor. This should only be done in a clean environment before the
    introduction to any gas that will be tested. An ideal environment to run this would be in standard air.
    */

    sensorValue = sensorValueCalculation();
    __Ro__ = sensorValue/9.83; //The Ro value is the resistance ratio in clean air (9.83). Needed for Rs/Ro calc.
}

float *GasSensor::getData(){
    /*
    The getData() function will get and calculate data from the sensor and return an array. This array will hold the
    following in the following order:

        Element 1: The raw resistance value from the sensor
        Element 2: The resistance ration from the sensor
        Element 3: The digital warning for the sensor
    */

    gasValue = sensorValueCalculation();
    gasRatio = gasValue/__Ro__; // raw ration of test gas (gasValue) to standard atmosphere (calValue).
    digitalInput = digitalRead(__dPin__);
    returnArray[0] = gasValue;
    returnArray[1] = gasRatio;
    returnArray[2] = digitalInput;
    return returnArray;
}

float GasSensor::sensorValueCalculation(){
    /*Got this equation from the website:
        https://www.instructables.com/id/How-to-Detect-Concentration-of-Gas-by-Using-MQ2-Se/
    */
    sensorRawValue=0;
    voltage = 0;
    for (int i = 0; i<100 ; i++){
        voltage = analogRead(__aPin__);
        sensorRawValue += (float) (__RL_Value__*(1023-voltage)/voltage);
    }

    return sensorRawValue = sensorRawValue/100;
}






