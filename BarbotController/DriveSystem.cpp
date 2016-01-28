#include "DriveSystem.h"


DriveSystem::DriveSystem() {
    this->stepper = new StepperMotor(DRIVE_ENABLE,DRIVE_STEP,DRIVE_DIR);
    this->stepper->stepSpeed(6);
    pinMode(DRIVE_ENDSTOP_PIN,INPUT);
    digitalWrite(DRIVE_ENDSTOP_PIN,HIGH);
}

void DriveSystem::up(int step) {
    stepper->setDirection(StepperMotor::LEFT);
    stepper->step(step);
}

void DriveSystem::down() {
    stepper->setDirection(StepperMotor::RIGHT);
    while (digitalRead(DRIVE_ENDSTOP_PIN) == 0) {
        stepper->step(10);
    }
}

void DriveSystem::down(int step) {
    stepper->setDirection(StepperMotor::RIGHT);
    stepper->step(step);
}

void DriveSystem::fullUp() {
    this->up(30000);
    this->up(30000);
    if (this->offset > 0) {
        Serial.print("Adding offset ");
        Serial.print(this->offset,DEC);
        Serial.println();
    } 
}

void DriveSystem::halfUp() {
    this->up(20000);
    this->up(20000);
    if (this->offset > 0) {
        Serial.print("Adding offset ");
        Serial.print(this->offset,DEC);
        Serial.println();
    } 
}

void DriveSystem::halfDown() {
    this->down(20000);
    this->down(20000);
    if (this->offset > 0) {
        Serial.print("Adding offset ");
        Serial.print(this->offset,DEC);
        Serial.println();
    }
}

void DriveSystem::setOffset(int offset) {
    this->offset = offset;
}

