#include <string>
#ifndef OSC_JOINT_H
#define OSC_JOINT_H

void jointInit(std::string name, int number, int pinStep, int pinDir, int totalStep,
    float startingRotation, float minRotation, float maxRotation, int rotationType, float deadband, int maxStepping);
float jointGetRotation(std::string name);
int jointGetPosition(std::string name);
int jointGetStepPin(std::string name);
int jointGetDirPin(std::string name);
int jointGetTotalStep(std::string name);
void jointSetTargetRotation(std::string name, float targetRotation);
void jointCreateTargetRotation(std::string name, float potValue);
void jointSetPosition(std::string name, int pos);
int getJointNumber(int pin);
int getRotationType(std::string name);
float jointGetTargetRotation(std::string name);
int validateJoint(std::string name);
float jointGetDeadband(std::string name);
int jointGetMaxStepping(std::string name);


#endif