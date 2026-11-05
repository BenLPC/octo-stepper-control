#include "osc_position.h"
#include <Arduino.h>
#include <math.h>

int getPosition(int totalStep, float rotation, int rotationType)  //returns signed position of motor in number of steps for a given rotation in degrees (rotationType) or radians (!rotationType).
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
  /* if (DEBUG) {
    Serial.print("(DEBUG) getPosition(): Got position value: ");
    Serial.print(x);
    Serial.print(".\n");
  } */
  return x;
}