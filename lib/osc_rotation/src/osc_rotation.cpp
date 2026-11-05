#include "osc_rotation.h"
#define _USE_MATH_DEFINES
#include <math.h>

float restrictRotationDomain(float rotation, float minRotation, float maxRotation, int rotationType) {  //returns any rotation value as the corresponding rotation within a domain restriction in degrees (rotationType) or radians (!rotationType).
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

float getRotation(int totalStep, int stepPosition, int rotationType) {  //returns signed rotation of motor in degrees (rotationType) or radians (!rotationType).

  int x;

  if (rotationType) {
    float increment = (float)360 / totalStep;
    x = increment * stepPosition;
  }
  if (!rotationType) {
    float increment = (float)(2 * M_PI) / totalStep;
    x = increment * stepPosition;
  }
// historic debug output, needs changing for new modular codebase
/*   if (DEBUG) {
    Serial.print("(DEBUG) getRotation(): Got rotation value: ");
    Serial.print(x);
    Serial.print(".\n");
  } */
  return x;
}