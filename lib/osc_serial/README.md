# osc_serial Library Documentation

## `getPotArray()`

### Description

Gets the potentiometer values over Serial using the `TX` and `RX` pins.

### Parameters

None.

### Returns

The `int*` address of the first value of the pot array. `potArray` is currently only six values long due to historic use. The remote needs two more pots and new code before eight potentiometers are fully supported.

## `usePotRotations()`

### Description

Calls `getPotArray` and uses the values to call `jointCreateTargetRotation` for all eight joints.

### Parameters

**`std::string name`**
: a string representing the motor in the format `"joint#"` for 1-8

### Returns

Void.