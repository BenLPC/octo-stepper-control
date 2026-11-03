#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

//toggle log
#define LOG 0
//toggle debug
#define DEBUG 0
//TESTING should be left as one, and used to substitute log and debug when only single print blocks are wanted.
#define TESTING 1

//defaults for ROTATIONTYPE, TOTALSTEP, STEPPOSITION, MINROTATION, MAXROTATION. Used if .init() function isn't called.
#define DFLT_ROTATIONTYPE 1
#define DFLT_TOTALSTEP 200
#define DFLT_STEPPOSITION 0
#define DFLT_TARGETROTATION 0
#define DFLT_MINROTATION 0.00
#define DFLT_MAXROTATION 360.00

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

//custom functions

float restrictRotationDomain(float rotation, float minRotation, float maxRotation, bool rotationType) {  //returns any rotation value as the corresponding rotation within a domain restriction in degrees (rotationType) or radians (!rotationType).
  if (rotationType) {
    while (rotation > maxRotation) {
      rotation = rotation - 360;
    }
    while (rotation < minRotation) {
      rotation = rotation + 360;
    }
  }
  if (!rotationType) {
    while (rotation > maxRotation) {
      rotation = rotation - (2 * M_PI);
    }
    while (rotation < minRotation) {
      rotation = rotation + (2 * M_PI);
    }
  }
  return rotation;
}

float getRotation(int totalStep, int stepPosition, bool rotationType) {  //returns signed rotation of motor in degrees (rotationType) or radians (!rotationType).

  int x;

  if (rotationType) {
    float increment = (float)360 / totalStep;
    x = increment * stepPosition;
  }
  if (!rotationType) {
    float increment = (float)(2 * M_PI) / totalStep;
    x = increment * stepPosition;
  }
  if (DEBUG) {
    Serial.print("(DEBUG) getRotation(): Got rotation value: ");
    Serial.print(x);
    Serial.print(".\n");
  }
  return x;
}

int getPosition(int totalStep, float rotation, bool rotationType)  //returns signed position of motor in number of steps for a given rotation in degrees (rotationType) or radians (!rotationType).
{

  int x;
  /*if (DEBUG) {
    Serial.print(totalStep);
    Serial.print(rotation);
    Serial.print(rotationType);
  }*/

  if (rotationType) {
    float increment = (float)360 / totalStep;
    x = round(rotation / increment);
  }
  if (!rotationType) {
    float increment = (float)(2 * M_PI) / totalStep;
    x = round(rotation / increment);
  }
  if (DEBUG) {
    Serial.print("(DEBUG) getPosition(): Got position value: ");
    Serial.print(x);
    Serial.print(".\n");
  }
  return x;
}

struct joint {                            //struct for joint info, methods restricted to min/max rotations whereas functions outside of struct can be unrestricted i.e. flywheels. This allows non-joint struct motors to share outside functions.
  int NUMBER;                             //value set by init().
  int PINDIR;                             //value set by init(), DEFAULTS TO 2.
  int PINSTEP;                            //value set by init(), DEFAULTS TO 3.
  bool ROTATIONTYPE = DFLT_ROTATIONTYPE;  //value set by init(), DEFAULTS TO DFLT_ROTATIONTYPE.
  int TOTALSTEP = DFLT_TOTALSTEP;         //value set by init(), DEFAULTS TO DFLT_TOTALSTEP.
  int STEPPOSITION = DFLT_STEPPOSITION;   //value set by init(), DEFAULTS TO DFLT_STEPPOSITION.
  float TARGETROTATION;                   //value set by init(), DEFAULTS TO DFLT_TARGETROTATION.
  float MINROTATION = DFLT_MINROTATION;   //value set by init(), DEFAULTS TO DFLT_MINROTATION.
  float MAXROTATION = DFLT_MAXROTATION;   //value set by init(), DEFAULTS TO DFLT_MAXROTATION.

  void jointInit(int number, int pinStep, int pinDir, int totalStep, float startingRotation, float minRotation, float maxRotation, int rotationType) {  //assign values to joint with proper adjustments for calculation.
    NUMBER = number;
    PINSTEP = pinStep;
    PINDIR = pinDir;
    TOTALSTEP = totalStep;
    ROTATIONTYPE = rotationType;
    MINROTATION = minRotation;
    MAXROTATION = maxRotation;

    pinMode(PINDIR, OUTPUT);
    pinMode(PINSTEP, OUTPUT);

    startingRotation = restrictRotationDomain(startingRotation, MINROTATION, MAXROTATION, ROTATIONTYPE);
    STEPPOSITION = getPosition(TOTALSTEP, startingRotation, rotationType);

    if (LOG) {
      Serial.print("(LOG) jointInit(): Motor ");
      Serial.print(NUMBER);
      Serial.print(" has been initialised with the following values:\n");
      Serial.print("- NUMBER = ");
      Serial.print(NUMBER);
      Serial.print(",\n");
      Serial.print("- PINSTEP = ");
      Serial.print(PINSTEP);
      Serial.print(",\n");
      Serial.print("- PINDIR = ");
      Serial.print(PINDIR);
      Serial.print(",\n");
      Serial.print("- TOTALSTEP = ");
      Serial.print(TOTALSTEP);
      Serial.print(",\n");
      Serial.print("- STEPPOSITION = ");
      Serial.print(STEPPOSITION);
      Serial.print(",\n");
      Serial.print("- ROTATIONTYPE = ");
      Serial.print(ROTATIONTYPE);
      Serial.print(".\n");
      Serial.print("- MINROTATION = ");
      Serial.print(MINROTATION);
      Serial.print(".\n");
      Serial.print("- MAXROTATION = ");
      Serial.print(MAXROTATION);
      Serial.print(".\n");
    }
  }

  int jointGetPosition() {  //returns STEPPOSITION restricted by min/max rotations.
    STEPPOSITION = getPosition(TOTALSTEP, restrictRotationDomain(getRotation(TOTALSTEP, STEPPOSITION, ROTATIONTYPE), MINROTATION, MAXROTATION, ROTATIONTYPE), ROTATIONTYPE);
    if (DEBUG) {
      Serial.print("(DEBUG) jointGetPosition(): Got J");
      Serial.print(NUMBER);
      Serial.print(" STEPPOSITION: ");
      Serial.print(STEPPOSITION);
      Serial.print(".\n");
    }
    return STEPPOSITION;
  }

  float jointGetRotation() {  //returns current joint rotation restricted by min/max rotations (not stored in struct).
    float rotation = restrictRotationDomain(getRotation(TOTALSTEP, STEPPOSITION, ROTATIONTYPE), MINROTATION, MAXROTATION, ROTATIONTYPE);
    if (DEBUG) {
      Serial.print("(DEBUG) jointGetRotation(): Got J");
      Serial.print(NUMBER);
      Serial.print(" rotation: ");
      Serial.print(rotation);
      Serial.print(".\n");
    }
    return rotation;
  }

  void jointSetTargetRotation(float targetRotation) {  //limits targetRotation to rotation domain and sets TARGETROTATION
    TARGETROTATION = restrictRotationDomain(targetRotation, MINROTATION, MAXROTATION, ROTATIONTYPE);
    if (LOG) {
      Serial.print("(LOG) jointSetTargetRotation(): Set TARGETROTATION = ");
      Serial.print(TARGETROTATION);
      Serial.print(".\n");
    }
  }

  void jointCreateTargetRotation(float potValue) {  //converts 1024 bit potValue to targetRotation, calls jointSetTargetRotation
    if (ROTATIONTYPE) {
      float x = (float)360 / 1024;
      float newTargetRotation = (float)potValue * x;
      if (abs(newTargetRotation - TARGETROTATION) > 5) {
        jointSetTargetRotation(newTargetRotation);
      }
    }
    if (!ROTATIONTYPE) {
      float x = (float)(2 * M_PI) / 1024;
      float newTargetRotation = (float)potValue * x;
      if (abs(newTargetRotation - TARGETROTATION) > 5) {
        jointSetTargetRotation(newTargetRotation);
      }
    }
  }
};

//define joints
joint joint1, joint2, joint3, joint4, joint5, joint6;
joint* jointsArray[] = { &joint1, &joint2, &joint3, &joint4, &joint5, &joint6 };

int getJointNumber(int pin) {  //returns NUMBER value for a joint struct if any joint struct has int pin as PINDIR or PINSTEP value. Returns 1 for success, 0 for failure and -1 for error.
  int isJointNumber = -1;
  for (int i = 0; i < (sizeof(jointsArray) / sizeof(jointsArray[0])); i++) {
    if (pin == (*jointsArray[i]).PINDIR || pin == (*jointsArray[i]).PINSTEP) {
      if (DEBUG) {
        Serial.print("(DEBUG) getJointNumber(): Got joint number = ");
        Serial.print((*jointsArray[i]).NUMBER);
        Serial.print("\n");
      }
      isJointNumber = 1;
      return (*jointsArray[i]).NUMBER;
    }
  }
  if (isJointNumber != 1) {
    if (DEBUG) {
      Serial.print("(DEBUG) getJointNumber(): Did not get joint number.");
    }
    return 0;
  }
  return -1;
}

int turnMotor(int totalStep, int stepPosition, float targetRotation, bool rotationType, int pinDir, int pinStep) {  //moves motor to target rotation. Returns 1 for success, 0 for failure and -1 for error.
  //get jointNumber in order to increment/decrement STEPPOSITION later on
  int jointNumber = getJointNumber(pinDir);
  if (jointNumber == 0 && DEBUG == 1) { Serial.print("(DEBUG) turnMotor(): Did not get a joint number from getJointNumber().\n"); }
  int jointArrayIndex = jointNumber - 1;

  if (jointNumber) {
    (*jointsArray[jointArrayIndex]).TARGETROTATION = targetRotation;
  }

  int targetPosition = getPosition(totalStep, targetRotation, 1);
  //debug
  if (DEBUG) {
    Serial.print("(DEBUG) turnMotor(): totalStep = ");
    Serial.print(totalStep);
    Serial.print(".\n");
  }
  if (DEBUG) {
    Serial.print("(DEBUG) turnMotor(): stepPosition = ");
    Serial.print(stepPosition);
    Serial.print(".\n");
  }
  if (DEBUG) {
    Serial.print("(DEBUG) turnMotor(): targetRotation = ");
    Serial.print(targetRotation);
    Serial.print(".\n");
  }
  if (DEBUG) {
    Serial.print("(DEBUG) turnMotor(): pinDir = ");
    Serial.print(pinDir);
    Serial.print(".\n");
  }
  if (DEBUG) {
    Serial.print("(DEBUG) turnMotor(): pinStep = ");
    Serial.print(pinStep);
    Serial.print(".\n");
  }
  if (DEBUG) {
    Serial.print("(DEBUG) turnMotor(): targetPosition = ");
    Serial.print(targetPosition);
    Serial.print(".\n");
  }

  //decide direction for target position
  int whichDir;
  if (stepPosition < targetPosition) {
    whichDir = 1;
  }
  if (stepPosition > targetPosition) {
    whichDir = 0;
  }
  if (stepPosition == targetPosition) {
    if (DEBUG) {
      Serial.print("(DEBUG) turnMotor(): Successfully reached position for motor on pin ");
      Serial.print(pinStep);
      Serial.print(".\n");
    }
    return 1;
  }

  //debug
  if (DEBUG) {
    Serial.print("(DEBUG) turnMotor(): whichDir = ");
    Serial.print(whichDir);
    Serial.print(".\n");
  }
  //set direction
  if (whichDir) {
    digitalWrite(pinDir, HIGH);
  } else {
    digitalWrite(pinDir, LOW);
  }

  //determine number of steps required
  int stepsRequired = abs(targetPosition - stepPosition);
  if (DEBUG) {
    Serial.print("(DEBUG) turnMotor(): stepsRequired = ");
    Serial.print(stepsRequired);
    Serial.print(".\n");
  }

  //write to motor
  for (int i = 0; i < stepsRequired; i++) {
    digitalWrite(pinStep, HIGH);
    delayMicroseconds(1000);
    digitalWrite(pinStep, LOW);
    delayMicroseconds(1000);
    if (whichDir) {
      if (jointNumber) {
        ++(*jointsArray[jointArrayIndex]).STEPPOSITION;
      }
      ++stepPosition;
    } else {
      if (jointNumber) {
        --(*jointsArray[jointArrayIndex]).STEPPOSITION;
      }
      --stepPosition;
    }
  }

  //return
  if (stepPosition == targetPosition) {
    if (LOG) {
      Serial.print("(LOG) turnMotor(): Successfully reached position for motor on pin ");
      Serial.print(pinStep);
      Serial.print(".\n\n\n");
    }
    return 1;
  } else if (!(stepPosition == targetPosition)) {
    if (LOG) {
      Serial.print("(LOG) turnMotor(): Failed to reach position for motor on pin ");
      Serial.print(pinStep);
      Serial.print(".\n\n\n");
    }
    return 0;
  }
  return -1;
}

int updateJointPositions() {
  int numberJointsCompleted = 0;
  numberJointsCompleted = numberJointsCompleted + turnMotor(joint1.TOTALSTEP, joint1.jointGetPosition(), joint1.TARGETROTATION, joint1.ROTATIONTYPE, joint1.PINDIR, joint1.PINSTEP);
  numberJointsCompleted = numberJointsCompleted + turnMotor(joint2.TOTALSTEP, joint2.jointGetPosition(), joint2.TARGETROTATION, joint2.ROTATIONTYPE, joint2.PINDIR, joint2.PINSTEP);
  numberJointsCompleted = numberJointsCompleted + turnMotor(joint3.TOTALSTEP, joint3.jointGetPosition(), joint3.TARGETROTATION, joint3.ROTATIONTYPE, joint3.PINDIR, joint3.PINSTEP);
  numberJointsCompleted = numberJointsCompleted + turnMotor(joint4.TOTALSTEP, joint4.jointGetPosition(), joint4.TARGETROTATION, joint4.ROTATIONTYPE, joint4.PINDIR, joint4.PINSTEP);
  numberJointsCompleted = numberJointsCompleted + turnMotor(joint5.TOTALSTEP, joint5.jointGetPosition(), joint5.TARGETROTATION, joint5.ROTATIONTYPE, joint5.PINDIR, joint5.PINSTEP);
  numberJointsCompleted = numberJointsCompleted + turnMotor(joint6.TOTALSTEP, joint6.jointGetPosition(), joint6.TARGETROTATION, joint6.ROTATIONTYPE, joint6.PINDIR, joint6.PINSTEP);
  return numberJointsCompleted;
}

void setup() {  //Arduino setup.
  Serial.begin(9600);

  joint1.jointInit(1, joint1_pinStep, joint1_pinDir, DFLT_TOTALSTEP, 0, DFLT_MINROTATION, DFLT_MAXROTATION, DFLT_ROTATIONTYPE);
  delay(100);
  joint2.jointInit(2, joint2_pinStep, joint2_pinDir, DFLT_TOTALSTEP, 0, DFLT_MINROTATION, DFLT_MAXROTATION, DFLT_ROTATIONTYPE);
  delay(100);
  joint3.jointInit(3, joint3_pinStep, joint3_pinDir, DFLT_TOTALSTEP, 0, DFLT_MINROTATION, DFLT_MAXROTATION, DFLT_ROTATIONTYPE);
  delay(100);
  joint4.jointInit(4, joint4_pinStep, joint4_pinDir, DFLT_TOTALSTEP, 0, DFLT_MINROTATION, DFLT_MAXROTATION, DFLT_ROTATIONTYPE);
  delay(100);
  joint5.jointInit(5, joint5_pinStep, joint5_pinDir, DFLT_TOTALSTEP, 0, DFLT_MINROTATION, DFLT_MAXROTATION, DFLT_ROTATIONTYPE);
  delay(100);
  joint6.jointInit(6, joint6_pinStep, joint6_pinDir, DFLT_TOTALSTEP, 0, DFLT_MINROTATION, DFLT_MAXROTATION, DFLT_ROTATIONTYPE);
  delay(100);
}

/*float createTargetRotation (int jointNumber, byte potValue) {
  Serial.print (potValue);
  Serial.print ("\n");
  if ((*jointsArray[jointNumber]).ROTATIONTYPE) {
    float x = (float) 360 / 4096;
    float newTargetRotation = (float) potValue * x;
    Serial.print (newTargetRotation);
    Serial.print ("\n");
    Serial.print ("\n");
    if (abs(newTargetRotation - (*jointsArray[jointNumber]).TARGETROTATION) > 5) {
      (*jointsArray[jointNumber]).TARGETROTATION = newTargetRotation;
    }
  }
  if (!(*jointsArray[jointNumber]).ROTATIONTYPE) {
    float x = (float) (2*M_PI) / 4096;
    float newTargetRotation = (float) potValue * x;
    Serial.print (newTargetRotation);
    Serial.print ("\n");
    Serial.print ("\n");
    if (abs(newTargetRotation - (*jointsArray[jointNumber]).TARGETROTATION) > 5) {
      (*jointsArray[jointNumber]).TARGETROTATION = newTargetRotation;
      Serial.print ((*jointsArray[jointNumber]).TARGETROTATION);
      Serial.print ("\n");
      Serial.print ("\n");
    }
  }
}*/

bool newData = false;

void loop() {  //Arduino loop.

  int potArray[6] = { 0, 0, 0, 0, 0, 0 };
  static bool recvInProgress = false;
  static byte ndx = 0;
  const char startMarker = 60;  //ASCII value for '<'
  const char endMarker = 62;    //ASCII value for '>'
  uint8_t recvByte;             //using little-endian
  static uint8_t low;           //using little-endian
  static bool haveLow = false;
  static uint8_t high;  //using little-endian
  static int ndxByte = 0;


  while (Serial.available() > 0 && newData == false) {
    recvByte = Serial.read();
    if (recvInProgress == true) {
      if (recvByte != endMarker) {
        if (!haveLow) {
          low = recvByte;
          haveLow = true;
        } else {
          high = recvByte;
          int potValueIn = ((uint32_t)high << 8) | low;
          potArray[ndxByte] = potValueIn;
          haveLow = false;
          ndxByte++;
        }
        ndx++;
      } else {
        recvInProgress = false;
        ndx = 0;
        ndxByte = 0;
        high = 0;
        low = 0;
        joint1.jointCreateTargetRotation(potArray[0]);
        Serial.println(potArray[0]);
        joint2.jointCreateTargetRotation(potArray[1]);
        Serial.println(potArray[1]);
        joint3.jointCreateTargetRotation(potArray[2]);
        Serial.println(potArray[2]);
        joint4.jointCreateTargetRotation(potArray[3]);
        Serial.println(potArray[3]);
        joint5.jointCreateTargetRotation(potArray[4]);
        Serial.println(potArray[4]);
        joint6.jointCreateTargetRotation(potArray[5]);
        Serial.println(potArray[5]);
        newData = true;
      }
    } else if (recvByte == startMarker) {
      Serial.print("[7]");
      recvInProgress = true;
    }
  }

  turnMotor(joint1.TOTALSTEP, joint1.jointGetPosition(), joint1.TARGETROTATION, joint1.ROTATIONTYPE, joint1.PINDIR, joint1.PINSTEP);
  turnMotor(joint2.TOTALSTEP, joint2.jointGetPosition(), joint2.TARGETROTATION, joint2.ROTATIONTYPE, joint2.PINDIR, joint2.PINSTEP);
  turnMotor(joint3.TOTALSTEP, joint3.jointGetPosition(), joint3.TARGETROTATION, joint3.ROTATIONTYPE, joint3.PINDIR, joint3.PINSTEP);
  turnMotor(joint4.TOTALSTEP, joint4.jointGetPosition(), joint4.TARGETROTATION, joint4.ROTATIONTYPE, joint4.PINDIR, joint4.PINSTEP);
  turnMotor(joint5.TOTALSTEP, joint5.jointGetPosition(), joint5.TARGETROTATION, joint5.ROTATIONTYPE, joint5.PINDIR, joint5.PINSTEP);
  turnMotor(joint6.TOTALSTEP, joint6.jointGetPosition(), joint6.TARGETROTATION, joint6.ROTATIONTYPE, joint6.PINDIR, joint6.PINSTEP);
  newData = false;
  delay(50);
  /*int successes = updateJointPositions();
  if(successes < 6) {
    if (DEBUG) {
      Serial.print("(Debug) loop(): not all joints reached their positions.");
    }
  }
  joint1.jointSetTargetRotation(joint1.TARGETROTATION);
  joint2.jointSetTargetRotation(joint2.TARGETROTATION + 90);
  joint3.jointSetTargetRotation(joint3.TARGETROTATION + 90);
  joint4.jointSetTargetRotation(joint4.TARGETROTATION + 90);
  joint5.jointSetTargetRotation(joint5.TARGETROTATION + 90);
  joint6.jointSetTargetRotation(joint6.TARGETROTATION + 90);
  delay(1000);*/
}