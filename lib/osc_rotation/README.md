# osc_rotation Library Documentation

## `restrictRotationDomain()`

### Description

Confines a rotation value to a domain with minimum and maximum angular displacement i.e. (-Pi, Pi) or (0, 2Pi) but also other intervals.

### Parameters

**`float rotation`**
: a given rotation value, could be currentRotation, targetRotation or other angular position

**`float minRotation`**
: the minimum angular displacement that is wanted for the given rotation value

**`float maxRotation`**
: the maximum angular displacement that is wanted for the given rotation value

**`int rotationType`**
: a 0 or 1 integer (boolean) representing degrees and radians coordinate spaces respectively

### Returns

Returns float representing new rotation value within defined domain.

## `getRotation()`

### Description

Calculates angular displacement using steps. Inverse of `getPosition()` in `osc_position` library.

### Parameters

**`int totalStep`**
: the number of steps in a given period i.e. for stepper motors this would be 360 or 2Pi. Not necessarily the same as domain used in `restrictRotationDomain()`

**`int stepPosition`**
: the current signed step count e.g. 100 steps for Pi, -100 steps for -Pi with a typical stepper motor

**`int rotationType`**
: a 0 or 1 integer (boolean) representing degrees and radians coordinate spaces respectively

### Returns

Returns the float angular displacement in the coordinate space defined by rotationType.