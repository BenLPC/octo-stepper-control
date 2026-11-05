# osc_position Library Documentation

## `getPosition()`

### purpose

Calculates steps using angular displacement. Inverse of `getRotation()` in `osc_rotation` library.

### parameters

**`int totalStep`**
: the number of steps in a given period i.e. for stepper motors this would be 360 or 2Pi. Not necessarily the same as domain used in `restrictRotationDomain()`

**`float rotation`**
: a given rotation value, could be currentRotation, targetRotation or other angular position

**`int rotationType`**
: a 0 or 1 integer (boolean) representing degrees and radians coordinate spaces respectively

### return

Returns the int current step position.
