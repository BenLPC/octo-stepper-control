# osc_joint Library Documentation

## `jointInit()`

### Description

Set up a motor or "joint" with custom Parameters. Each motor can as such be set up individually.

### Parameters

**`std::string name`**
: a string representing the motor in the format `"joint#"` for 1-8

**`int number`**
: integer representing the joint number i.e. 1-8

**`int pinStep`**
he digital step pin for the motor

**`int dirPin`**
: the digital direction pin for the motor

**`int totalStep`**
 the number of steps in one revolution of the motor. Typically 200 but more for microstepping

**`float startingRotation`**
: the starting angular displacement of the motor. Easiest to bottom out potentiometers before powering and use zero starting rotation

**`float minRotation`**
: the minimum angular displacement that is wanted for the given rotation value

**`float maxrotation`**
: the maximum angular displacement that is wanted for the given rotation value

**`int rotationType`**
: a 0 or 1 integer (boolean) representing degrees and radians coordinate spaces respectively

**`float deadband`**
: the minimum amount of angular displacement between target and actual position required before a motor is rotated

**`int maxStepping`**
: the maximum amount of steps each motor is allowed to make per cycle

### Returns

Void.

## `jointGetRotation()`

### Description

Get the current rotation of a joint. Uses `rotationType` set by `jointInit()`.

### Parameters

**`std::string name`**
: a string representing the motor in the format `"joint#"` for 1-8

### Returns

The float rotation.

## `jointGetPosition()`

### Description

Get the current step position of a joint.

### Parameters

**`std::string name`**
: a string representing the motor in the format `"joint#"` for 1-8

### Returns

The int step position.

## `jointGetStepPin()`

### Description

Get the step pin of a joint. Used commonly within osc libraries.

### Parameters

**`std::string name`**
: a string representing the motor in the format `"joint#"` for 1-8

### Returns

The int step pin for the joint.

## `jointGetDirPin()`

### Description

Get the direction pin of a joint. Used commonly within osc libraries.

### Parameters

**`std::string name`**
: a string representing the motor in the format `"joint#"` for 1-8

### Returns

The int direction pin for the joint.

## `jointGetTotalStep()`

### Description

Get the total steps per revolution of the joint.

### Parameters

**`std::string name`**
: a string representing the motor in the format `"joint#"` for 1-8

### Returns

The int total steps per revolution of the joint.

## `jointSetTargetRotation()`

### Description

Set the target rotation for a joint. Uses `rotationType` set by `jointInit()`.

### Parameters

**`std::string name`**
: a string representing the motor in the format `"joint#"` for 1-8

**`float targetRotation`**
: a float target angular position.

### Returns

Void.

## `jointCreateTargetRotation()`

### Description

Sets the target rotation for a joint using a pot value. Calls `jointSetTargetRotation()` after converting pot value to angular position using min/max rotations and rotation type of the joint.

### Parameters

**`std::string name`**
: a string representing the motor in the format `"joint#"` for 1-8

**`float potValue`**
: the float value of a potentiometer.

### Returns

Void.

## `jointSetPosition()`

### Description

Update the step position of a joint.

### Parameters

**`std::string name`**
: a string representing the motor in the format `"joint#"` for 1-8

**`int stepPosition`**
: the new step position of the joint

### Returns

Void

## `getJointNumber()`

### Description

Get the joint number of a joint using that joint's `stepPin` or `dirPin`. A historic function that is superfluous along with the `number` parameter in `jointInit()`.

### Parameters

**`int pin`**
: the digitial step or direction pin of the joint

### Returns

The int joint number.

## `getRotationType()`

### Description

Gets the coordinate space of angular position, where 0 is using degrees and 1 is using radians.

### Parameters

**`std::string name`**
: a string representing the motor in the format `"joint#"` for 1-8

### Returns

The int rotation type where 0 is using degrees and 1 is using radians.

## `jointGetTargetRotation()`

### Description

Gets the target rotation of a joint. Uses `rotationType` set by `jointInit()`.

### Parameters

**`std::string name`**
: a string representing the motor in the format `"joint#"` for 1-8

### Returns

The float target rotation.

## `validateJoint()`

### Description

Checks whether `name` is a sstandard joint name e.g. `"joint5"`. Mostly for public use outside of `osc_joint`.

### Parameters

**`std::string name`**
: a string representing the motor in the format `"joint#"` for 1-8

### Returns

An int of 0 or 1 acting as boolean for if `name` isn't or is a valid joint name.

## `jointGetDeadband()`

### Description

Gets the deadband for a joint. The deadband is the minimum change in a joint's target position required for the motor to actually move.

### Parameters

**`std::string name`**
: a string representing the motor in the format `"joint#"` for 1-8

### Returns

The float deadband.

## `jointGetMaxStepping()`

### Description

Gets the max stepping allowed for a joint in a given cycle of `loop()` inside `main.cpp`.

### Parameters

**`std::string name`**
: a string representing the motor in the format `"joint#"` for 1-8

### Returns

The int max stepping.