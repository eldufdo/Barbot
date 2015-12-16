#include "StepperMotor.h"

StepperMotor::StepperMotor(char enablePin,char stepPin,char dirPin) {
    pinMode(enablePin,OUTPUT);
    pinMode(stepPin,OUTPUT);
    pinMode(dirPin,OUTPUT);
    this->stepPin = stepPin;
    this->dirPin = dirPin;
    this->enablePin = enablePin;
    this->speed = 600;
    digitalWrite(this->enablePin,LOW); // enable motor on init
}

void StepperMotor::step(int steps) {
    for (int i = 0; i < steps; i++) {
        digitalWrite(this->stepPin,HIGH);
        delayMicroseconds(this->speed);
        digitalWrite(this->stepPin,LOW);
        delayMicroseconds(this->speed);
    } 
}

void StepperMotor::stepSpeed(int factor) {
	this->speed = 600/factor;
}

void StepperMotor::setDirection(Direction dir) {
    if (dir == LEFT) {
        digitalWrite(this->dirPin,LOW);
    } else {
	digitalWrite(this->dirPin,HIGH);
    }
}
