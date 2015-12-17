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
