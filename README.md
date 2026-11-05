# octo-stepper-control

> Octo Stepper Control (OSC) is a microcontroller program (Platform IO project) designed for eight Nema-17 stepper motors and an esp32 dev board with additional remote control via serial.

### latest changelog (1.0.1)

- rewrote codebase to be modular rather than one monolithic file

### notes

- The main controller program can still drive steppers without potentiometers, although there is currently no way to provide ongoing control without the pots. A web application would fix this in newer versions.
- The accompanying osc-stepper-remote code needs adjusting to take full advantage of eight potentiometers.
- Need to rework language around angular displacement/position and libraries to be more accurate.