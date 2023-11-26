#include <Arduino.h>
#include <EEPROM.h>
#include <Stepper.h>

int stepperMode; // Defines if the motor is active or inactive
const int stepsPerRevolution = 2048; // Number of steps per rotations
//Stepper myStepper = Stepper(stepsPerRevolution, 8, 9, 10, 11); // Stepper object
Stepper myStepper = Stepper(stepsPerRevolution, 9, 10, 11, 7);

void setup() {
  Serial.begin(9600);
  
  myStepper.setSpeed(10);  // Sets motor's speed

  stepperMode = EEPROM.read(0);
  if(stepperMode != 0 && stepperMode != 1 && stepperMode != 2) {  
    
    // The first power cycle is detected when the EEPROM value is not equal
    // to 0 or 1
    EEPROM.update(0, 1);
    stepperMode = 1;

  }

  if(stepperMode == 0) {

    // During the last power cycle, the stepper was inactive
    // We want it to be active turn clockwise
    EEPROM.update(0, 1);

  } else if(stepperMode == 1) {

    // During the last power cycle, the stepper was active and turning clockwise
    // We want it to be active and turn counterclockwise
    EEPROM.update(0, 2);

  } else if(stepperMode == 2) {

    // During the last power cycle, the stpper was active and turning counterclockwise
    // We want it to be inactive. 
    EEPROM.update(0, 0);

  }
}

void loop() {
  if(stepperMode == 1) { // The motor is set to turn clockwise
    Serial.println("CLOCKWISE");
    myStepper.step(stepsPerRevolution); 
  } else if(stepperMode == 2) { // The motor is set to turn unclockwise
    Serial.println("COUNTERCLOCKWISE");
    myStepper.step(-stepsPerRevolution);
  } else { // The motor is set to stop turning 
    Serial.println("STOPPED");
  }
}