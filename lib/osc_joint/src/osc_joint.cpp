#include "osc_joint.hpp"
#include <Arduino.h>
#include <osc_rotation.hpp>
#include <osc_position.hpp>
#include <unordered_map>
#include <string>

struct Joint {                            //struct for joint info, methods restricted to min/max rotations whereas functions outside of struct can be unrestricted i.e. flywheels. This allows non-joint struct motors to share outside functions.
    int NUMBER;                             //value set by init().
    int PINDIR;                             //value set by init(), DEFAULTS TO 2.
    int PINSTEP;                            //value set by init(), DEFAULTS TO 3.
    int ROTATIONTYPE;  //value set by init(), DEFAULTS TO DFLT_ROTATIONTYPE.
    int TOTALSTEP;         //value set by init(), DEFAULTS TO DFLT_TOTALSTEP.
    int STEPPOSITION;   //value set by init(), DEFAULTS TO DFLT_STEPPOSITION.
    int MAXSTEPPING;
    float TARGETROTATION;                   //value set by init(), DEFAULTS TO DFLT_TARGETROTATION.
    float MINROTATION;   //value set by init(), DEFAULTS TO DFLT_MINROTATION.
    float MAXROTATION;   //value set by init(), DEFAULTS TO DFLT_MAXROTATION.
    float DEADBAND; //value set by init(), DEFAULTS TO DFLT_DEADBAND.

    void __jointInit(int number, int pinStep, int pinDir, int totalStep, float startingRotation, float minRotation, float maxRotation, int rotationType, float deadband, int maxStepping) {  //assign values to joint with proper adjustments for calculation.
        NUMBER = number;
        PINSTEP = pinStep;
        PINDIR = pinDir;
        TOTALSTEP = totalStep;
        ROTATIONTYPE = rotationType;
        MINROTATION = minRotation;
        MAXROTATION = maxRotation;
        DEADBAND = deadband;
        MAXSTEPPING = maxStepping;

        pinMode(PINDIR, OUTPUT);
        pinMode(PINSTEP, OUTPUT);

        startingRotation = restrictRotationDomain(startingRotation, MINROTATION, MAXROTATION, ROTATIONTYPE);
        STEPPOSITION = getPosition(TOTALSTEP, startingRotation, rotationType);
    }

    void __jointSetTargetRotation(float targetRotation) {  //limits targetRotation to rotation domain and sets TARGETROTATION
        TARGETROTATION = restrictRotationDomain(targetRotation, MINROTATION, MAXROTATION, ROTATIONTYPE);
        /* if (LOG) {
        Serial.print("(LOG) jointSetTargetRotation(): Set TARGETROTATION = ");
        Serial.print(TARGETROTATION);
        Serial.print(".\n");
        } */
    }

    void __jointCreateTargetRotation(float potValue) {  //converts 1024 bit potValue to targetRotation, calls jointSetTargetRotation
        float range = MAXROTATION - MINROTATION;
        float newTargetRotation = MINROTATION + (potValue / 1024.0f) * range;
        if (fabsf(newTargetRotation - TARGETROTATION) > DEADBAND) {
            __jointSetTargetRotation(newTargetRotation);
        }
    }
};

std::unordered_map<std::string, Joint> joints = {
    {"joint1", {}},
    {"joint2", {}},
    {"joint3", {}},
    {"joint4", {}},
    {"joint5", {}},
    {"joint6", {}},
    {"joint7", {}},
    {"joint8", {}},
};

void jointInit(std::string name, int number, int pinStep, int pinDir, int totalStep,
    float startingRotation, float minRotation, float maxRotation, int rotationType, float deadband, int maxStepping) {
    auto test = joints.find(name);
    if (test != joints.end()) {
        test->second.__jointInit(number, pinStep, pinDir, totalStep, startingRotation, minRotation, maxRotation, rotationType, deadband, maxStepping);
    } else {
        Serial.print("Unknown joint name.\n"); //change when osc_serial
    }
}

float jointGetRotation(std::string name) {
    auto test = joints.find(name);
    if (test != joints.end()) {
        return getRotation(test->second.TOTALSTEP, test->second.STEPPOSITION, test->second.ROTATIONTYPE);
    }
    return 0;
}

int jointGetPosition(std::string name) {
    auto test = joints.find(name);
    if (test != joints.end()) {
        return test->second.STEPPOSITION;
    }
    return 0;
}

int jointGetStepPin(std::string name) {
    auto test = joints.find(name);
    if (test != joints.end()) {
        return test->second.PINSTEP;
    }
    return 0;
}

int jointGetDirPin(std::string name) {
    auto test = joints.find(name);
    if (test != joints.end()) {
        return test->second.PINDIR;
    }
    return 0;
}

int jointGetTotalStep(std::string name) {
    auto test = joints.find(name);
    if (test != joints.end()) {
        return test->second.TOTALSTEP;
    }
    return 0;
}

void jointSetTargetRotation(std::string name, float targetRotation) {
    auto test = joints.find(name);
    if (test != joints.end()) {
        test->second.__jointSetTargetRotation(targetRotation);
    } else {
        Serial.print("Unknown joint.\n"); //osc_serial
    }
}

void jointCreateTargetRotation(std::string name, float potValue) {
    auto test = joints.find(name);
    if (test != joints.end()) {
        test->second.__jointCreateTargetRotation(potValue);
    } else {
        throw "Unknown joint";
    }
}

void jointSetPosition(std::string name, int pos) {
    auto test = joints.find(name);
    if (test != joints.end()) {
        test->second.STEPPOSITION = pos;
    }
}

int getJointNumber(int pin) {
    for (auto &j : joints) {
        if (j.second.PINDIR == pin || j.second.PINSTEP == pin) {
            return j.second.NUMBER;
        }
    }
    return -1;
}

int getRotationType(std::string name) {
    auto test = joints.find(name);
    if (test != joints.end()) return test->second.ROTATIONTYPE;
    return -1;
}

float jointGetTargetRotation(std::string name) {
    auto test = joints.find(name);
    if (test != joints.end()) return test->second.TARGETROTATION;
    return 0;
}

float jointGetDeadband(std::string name) {
    auto test = joints.find(name);
    if (test != joints.end()) return test->second.DEADBAND;
    return 0;
}

int jointGetMaxStepping(std::string name) {
    auto test = joints.find(name);
    if (test != joints.end()) return test->second.MAXSTEPPING;
    return 0;
}

int validateJoint(std::string name) {
    auto test = joints.find(name);
    return (test != joints.end());
}