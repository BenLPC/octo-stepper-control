#include "osc_serial.hpp"
#include <Arduino.h>
#include <string>
#include <osc_joint.hpp>

int* getPotArray() {
    int newData = false;
    static int potArray[8] = { 0, 0, 0, 0, 0, 0, 0, 0};
    static int recvInProgress = false;
    const char startMarker = 60;  //ASCII value for '<'
    const char endMarker = 62;    //ASCII value for '>'
    uint8_t recvByte;             //using little-endian
    static uint8_t low;           //using little-endian
    static int haveLow = false;
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
                    if (ndxByte < 8) {
                        high = recvByte;
                        int potValueIn = ((uint32_t)high << 8) | low;
                        potArray[ndxByte] = potValueIn;
                        ndxByte++;
                    }
                    haveLow = false;
                    low = 0;
                }
            } else {
                recvInProgress = false;
                ndxByte = 0;
                high = 0;
                low = 0;
                haveLow = false;
                newData = true;
            }
        } else if (recvByte == startMarker) {
            haveLow = false;
            recvInProgress = true;
        }
    }
    if (newData) {
        return (int*)potArray;
    }
    return nullptr;
}

void usePotRotations() {
    int* potArray = getPotArray();
    if (potArray != nullptr) {
        jointCreateTargetRotation("joint1", *potArray);
        jointCreateTargetRotation("joint2", *(potArray+1));
        jointCreateTargetRotation("joint3", *(potArray+2));
        jointCreateTargetRotation("joint4", *(potArray+3));
        jointCreateTargetRotation("joint5", *(potArray+4));
        jointCreateTargetRotation("joint6", *(potArray+5));
        jointCreateTargetRotation("joint7", *(potArray+6));
        jointCreateTargetRotation("joint8", *(potArray+7));
    }
}
