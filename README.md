# bandClock
Arduino code compatible with Arduino Nano for building a stepper motor based "conveyor belt/band clock".
Uses a unipolar stepper motor and a U2004 Darlington Array.
motor connected to 5v to reduce overheating from battery.

# REQUIREMENTS
Arduino stepper library:
https://www.arduino.cc/en/reference/stepper

# user variables
float timingBeltLength = 1.163; //in meters
float spindleDiameter = 0.02; //in meters
float fullSpeedForReset = 10;
const int stepsPerRevolution = 200;

The above variables in the code should be changed according to your system.
timingBeltLength is the FULL length of the band in meters.
spindleDiameter is the circumference of whatever surrounds the shaft of the stepper motor.
fullSpeedForReset determines speed when button is pressed.
stepsPerRevolution depends on the stepper motor used. Normally this is 200.

# system variables

Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);
const int speedPin = 12;

myStepper - 8, 9, 10, and 11 refer to the output pins on the arduino.
speedPin refers to digital input pin where switch for reset is connected.
