# osc_motor Library Documentation

## `turnMotor()`

### Description

Attempts to drive a stepper motor to its target rotation. If the angular displacement to the new rotation position is larger than `maxSteps` then it will take more than one iteration of the `main.cpp` `loop()` to reach its new position ("progressing"). This is done so that each motor has an equal max blocking time, so that there is a hard limit on latency and all motors aren't blocked by one joint e.g. a wormgear with large bounds.

### Parameters

**`std::string name`**
: a string representing the motor in the format `"joint#"` for 1-8

**`float targetRotation`**
: a float target angular position

### Returns

An int of 0, 1 or 2 for failed, succeeded or progressed respectively.

## `turnAllMotors()`

### Description

Turns all joint by calling turnMotor() with each stored target rotation.

### Parameters

None.

### Returns

Void.