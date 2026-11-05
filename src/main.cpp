#include <Arduino.h>
#include <osc_lib.h>


//defaults for ROTATIONTYPE, TOTALSTEP, STEPPOSITION, MINROTATION, MAXROTATION. Used if .init() function isn't called.
#define DFLT_ROTATIONTYPE 1
#define DFLT_TOTALSTEP 200
#define DFLT_STEPPOSITION 0
#define DFLT_TARGETROTATION 0
#define DFLT_MINROTATION 0.00
#define DFLT_MAXROTATION 360.00
#define DFLT_DEADBAND 5
#define DFLT_STARTINGROTATION 0
#define DFLT_MAXSTEPPING 10

//motor 1 pins
#define joint1_pinDir 15
#define joint1_pinStep 2
//motor 2 pins
#define joint2_pinDir 4
#define joint2_pinStep 5
//motor 3 pins
#define joint3_pinDir 18
#define joint3_pinStep 19
//motor 4 pins
#define joint4_pinDir 21
#define joint4_pinStep 22
//motor 5 pins
#define joint5_pinDir 23
#define joint5_pinStep 13
//motor 6 pins
#define joint6_pinDir 14
#define joint6_pinStep 27
//motor 7 pins
#define joint7_pinDir 0 //undefined as of now, controller box only has six controllers atm
#define joint7_pinStep 0
//motor 8 pins
#define joint8_pinDir 0
#define joint8_pinStep 0

void setup() {  //Arduino setup.
  Serial.begin(9600);

  jointInit("joint1", 1, joint1_pinStep, joint1_pinDir, DFLT_TOTALSTEP, DFLT_STARTINGROTATION, DFLT_MINROTATION, DFLT_MAXROTATION, DFLT_ROTATIONTYPE, DFLT_DEADBAND, DFLT_MAXSTEPPING);
  delay(100);
  jointInit("joint2", 2, joint2_pinStep, joint2_pinDir, DFLT_TOTALSTEP, DFLT_STARTINGROTATION, DFLT_MINROTATION, DFLT_MAXROTATION, DFLT_ROTATIONTYPE, DFLT_DEADBAND, DFLT_MAXSTEPPING);
  delay(100);
  jointInit("joint3", 3, joint3_pinStep, joint3_pinDir, DFLT_TOTALSTEP, DFLT_STARTINGROTATION, DFLT_MINROTATION, DFLT_MAXROTATION, DFLT_ROTATIONTYPE, DFLT_DEADBAND, DFLT_MAXSTEPPING);
  delay(100);
  jointInit("joint4", 4, joint4_pinStep, joint4_pinDir, DFLT_TOTALSTEP, DFLT_STARTINGROTATION, DFLT_MINROTATION, DFLT_MAXROTATION, DFLT_ROTATIONTYPE, DFLT_DEADBAND, DFLT_MAXSTEPPING);
  delay(100);
  jointInit("joint5", 5, joint5_pinStep, joint5_pinDir, DFLT_TOTALSTEP, DFLT_STARTINGROTATION, DFLT_MINROTATION, 10*DFLT_MAXROTATION, DFLT_ROTATIONTYPE, DFLT_DEADBAND, DFLT_MAXSTEPPING);
  delay(100);
  jointInit("joint6", 6, joint6_pinStep, joint6_pinDir, DFLT_TOTALSTEP, DFLT_STARTINGROTATION, DFLT_MINROTATION, DFLT_MAXROTATION, DFLT_ROTATIONTYPE, DFLT_DEADBAND, DFLT_MAXSTEPPING);
  delay(100);
  jointInit("joint7", 7, joint7_pinStep, joint7_pinDir, DFLT_TOTALSTEP, DFLT_STARTINGROTATION, DFLT_MINROTATION, DFLT_MAXROTATION, DFLT_ROTATIONTYPE, DFLT_DEADBAND, DFLT_MAXSTEPPING);
  delay(100);
  jointInit("joint8", 8, joint8_pinStep, joint8_pinDir, DFLT_TOTALSTEP, DFLT_STARTINGROTATION, DFLT_MINROTATION, DFLT_MAXROTATION, DFLT_ROTATIONTYPE, DFLT_DEADBAND, DFLT_MAXSTEPPING);
  delay(100);
}

void loop() {  //Arduino loop.
  usePotRotations();

  turnMotor("joint1", jointGetTargetRotation("joint1"));
  turnMotor("joint2", jointGetTargetRotation("joint2"));
  turnMotor("joint3", jointGetTargetRotation("joint3"));
  turnMotor("joint4", jointGetTargetRotation("joint4"));
  turnMotor("joint5", jointGetTargetRotation("joint5"));
  turnMotor("joint6", jointGetTargetRotation("joint6"));
  /* turnMotor("joint7", jointGetRotation("joint7"));
  turnMotor("joint8", jointGetRotation("joint8")); */
}