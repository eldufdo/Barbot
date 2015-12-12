#include "StepperMotor.h"

StepperMotor::StepperMotor(char enablePin,char stepPin,char dirPin) {
    pinMode(enablePin,OUTPUT);
    pinMode(stepPin,OUTPUT);
    pinMode(dirPin,OUTPUT);
    this->stepPin = stepPin;
    this->dirPin = dirPin;
    this->enablePin = enablePin;
    digitalWrite(this->enablePin,LOW); // enable motor on init
}

void StepperMotor::step(int steps) {
    for (int i = 0; i < steps; i++) {
        digitalWrite(this->stepPin,HIGH);
        delayMicroseconds(200);
        digitalWrite(this->stepPin,LOW);
        delayMicroseconds(200);
    }   
}
