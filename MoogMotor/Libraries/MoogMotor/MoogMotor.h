/*
 * MoogMotor.h - Library for controlling Moog Smart Motors via HardwareSerial.
 * Created by Joe Ditz on Jan 27, 2021
 */

 #ifndef MoogMotor_h
 #define MoogMotor_h

 #include "Arduino.h"
 #include "HardwareSerial.h"

 class MoogMotor
 {
  public:
    enum MotorMode {POS, VEL, TOR};

    MoogMotor(HardwareSerial associatedSerial);
    boolean driveMotor(MotorMode operationMode, float value);
    void hault();
    void slowToStop();
    void initSerial();

  private:
    HardwareSerial *serial = NULL;
    MotorMode mode = POS;

    
  
 };

#endif
