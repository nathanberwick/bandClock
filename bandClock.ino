#include "RTClib.h"
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
float stepsPerSecond = stepsPerBand/86400; //24*60*60, or 24hrs into seconds.
double modfreturn;
float decimalDelay = modf(stepsPerSecond, &modfreturn);
int counterForRound = round(1/decimalDelay);
int counter = 1; //TODO: figure out whether this should be zero at startup
int previousSecond = 0;

//system variables
RTC_DS3231 rtc;
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);
const int speedPin = 12;
bool buttonState = false;

void setup()
{
  rtc.begin();
  pinMode(speedPin,INPUT);
  pinMode(13, OUTPUT);
  myStepper.setSpeed(fullSpeedForReset);
}
  
void loop() {
  DateTime currentTime = rtc.now();
  buttonState = digitalRead(speedPin);

  if (previousSecond != currentTime.second() && !buttonState) {
    previousSecond = currentTime.second();
    myStepper.step(decimalDelay);
    counter++;
    if (counter == counterForRound) {
      counter = 1;
      myStepper.step(1);
    }
  } else if (buttonState)
  {
    myStepper.step(1); //if button pressed, keep stepping at full speed.
  }
}
