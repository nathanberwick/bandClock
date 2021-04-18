#include <Stepper.h>
#include <math.h>

//changeable variables
float timingBeltLength = 200;//1.163; //in meters
float spindleDiameter = 0.02; //in meters
float fullSpeedForReset = 50;
const int stepsPerRevolution = 200;

//calculated variables
float stepLength = (spindleDiameter*PI)/stepsPerRevolution;
float stepsPerBand = timingBeltLength/stepLength;
float delayBetweenSteps = 86400000/stepsPerBand;
double modfreturn;
float decimalDelay = modf(delayBetweenSteps, &modfreturn);
int counterForRound = round(1/decimalDelay);
int counter = 1;
int intStepDelay = delayBetweenSteps;
//TODO: implement a counter system to add all the rounded bits together to make a "every x times, +1"

//system variables
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);
const int speedPin = 12;
bool buttonState = false;

void setup()
{
  pinMode(speedPin,INPUT);
  pinMode(13, OUTPUT);
  myStepper.setSpeed(fullSpeedForReset);
}
  
void loop()
{
    myStepper.step(1);
    for (int j = 0; j < intStepDelay; j++)
    {
      buttonState = digitalRead(speedPin);
      if (!buttonState)
      {
        delay(1);
      }
      counter++;
      if (counter == counterForRound)
      {
        digitalWrite(13, HIGH);
        delay(1);
        digitalWrite(13,LOW);
        counter = 1;
      }
  }
}
