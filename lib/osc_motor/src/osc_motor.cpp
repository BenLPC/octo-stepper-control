#include "osc_motor.h"
#include <Arduino.h>
#include <osc_joint.h>
#include <osc_position.h>
#include <string>

int turnMotor(std::string name, float targetRotation) {  //moves motor to target rotation. Returns 1 for success, 2 for progress and -1 for error.
    if (!validateJoint(name)) return -1;
    int stepPosition = jointGetPosition(name);
    int totalStep = jointGetTotalStep(name);
    int rotationType = getRotationType(name);
    int targetPosition = getPosition(totalStep, targetRotation, rotationType);
    int pinDir = jointGetDirPin(name);
    int pinStep = jointGetStepPin(name);
    int maxStepping = jointGetMaxStepping(name);
    

    //decide direction for target position
    int whichDir;
    if (stepPosition < targetPosition) {
        whichDir = 1;
    }
    if (stepPosition > targetPosition) {
        whichDir = 0;
    }
    if (stepPosition == targetPosition) {
        return 1;
    }

    //set direction
    if (whichDir) {
        digitalWrite(pinDir, HIGH);
    } else {
        digitalWrite(pinDir, LOW);
    }

    //determine number of steps required
    int stepsRequired = abs(targetPosition - stepPosition);
    int stepsNow;
    if (stepsRequired < maxStepping) {
        stepsNow = stepsRequired;
    } else {
        stepsNow = maxStepping;
    }


    //write to motor
    for (int i = 0; i < stepsNow; i++) {
        digitalWrite(pinStep, HIGH);
        delayMicroseconds(1000);
        digitalWrite(pinStep, LOW);
        delayMicroseconds(1000);
        if (whichDir) {
        ++stepPosition;
        jointSetPosition(name, stepPosition);
        } else {
        --stepPosition;
        jointSetPosition(name, stepPosition);
        }
    }

    //return
    if (stepPosition == targetPosition) {
        return 1;
    } else if (!(stepPosition == targetPosition)) {
        return 2;
    }
    return -1; //error
}