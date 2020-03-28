#include <GasSensor.h>

float *mq2Data = new float[3];
float *mq5Data = new float[3];
float *mq7Data = new float[3];

GasSensor mq2(A2,2,5);
GasSensor mq5(A3,3,5);
GasSensor mq7(A4,4,5);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mq2.sensorCalibration();
  mq5.sensorCalibration();
  mq7.sensorCalibration();
}

void loop() {
  // put your main code here, to run repeatedly:
  printData();
  delay (10);
  
}

void printData(){
  mq2Data = mq2.getData();
  mq5Data = mq5.getData();
  mq7Data = mq7.getData();
  Serial.print(mq2Data[1]);
  Serial.print(",");
  Serial.print(mq5Data[1]);
  Serial.print(",");
  Serial.print(mq7Data[1]);
  Serial.println();

}
