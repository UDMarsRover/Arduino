#include "HardwareSerial.h"
#include "MoogMotor.h"


#define led = 13;

#define startB = 12;
#define stopB = 11;
#define haultB = 10;

MoogMotor mot = MoogMotor(Serial);

void setup() {
  mot.initSerial();
  delay(1000);

  pinMode(led, OUTPUT);

  pinMode(startB, INPUT_PULLUP);
  pinMode(stopB, INPUT_PULLUP);
  pinMode(haultB, INPUT_PULLUP);
}

void loop() {
  st = digitalRead(startB);
  sp = digitalRead(stopB);
  ht = digitalRead(haultB);

  if (ht == LOW)//if hault button, hault
  {
    mot.hault();
    digitalWrite(led, LOW);
  }
  else if (sp == LOW)//if stop button, slow to stop
  {
    mot.slowToStop();
    digitalWrite(led, LOW);
  }
  else if (st == LOW)//if start button, start (velocity mode, quarter speed)
  {
    mot.driveMotor(MoogMotor::VEL, .25);
    digitalWrite(led, HIGH);
  }

  delay(250);
}
