#ifndef OSC_ROTATION_H
#define OSC_ROTATION_H

float restrictRotationDomain(float rotation, float minRotation, float maxRotation, int rotationType);
float getRotation(int totalStep, int stepPosition, int rotationType);

#endif