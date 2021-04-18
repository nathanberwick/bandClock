#include <Stepper.h>

//changeable variables
float timingBeltLength = 1.163; //in meters
float spindleDiameter = 0.02; //in meters
float fullSpeedForReset = 10;
const int stepsPerRevolution = 200;

//calculated variables
float stepLength = (spindleDiameter*PI)/stepsPerRevolution;
float stepsPerBand = timingBeltLength/stepLength;
float delayBetweenSteps = 86400000/stepsPerBand;
int intStepDelay = round(delayBetweenSteps);
//TODO: implement a counter system to add all the rounded bits together to make a "every x times, +1"

//system variables
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);
const int speedPin = 12;
bool buttonState = false;

void setup()
{
  pinMode(speedPin,INPUT);
  myStepper.setSpeed(fullSpeedForReset);
}
  
void loop()
{
  myStepper.step(1);
  for (int i = 0; i < intStepDelay; i++)
  {
    buttonState = digitalRead(speedPin);
    if (!buttonState)
    {
      delay(1);
    }
  }
}
