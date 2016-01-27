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

void StepperMotor::stepAccel(int steps) {
    int speed0, startSpeed;
    speed0 = startSpeed = this->speed * 1.1;
    char maxReached = 0;
    for (int i = 0; i < steps; i++) {
        if (maxReached == 0  && speed0 > this->speed) {
            speed0--;
            if (speed0 <= this->speed) {
                maxReached = 1;
                speed0 == this -> speed;
            }
        } 
        if ((steps - i) < startSpeed){
            speed0++;
        }
        digitalWrite(this->stepPin,HIGH);
        delayMicroseconds(speed0);
        digitalWrite(this->stepPin,LOW);
        delayMicroseconds(speed0);
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
