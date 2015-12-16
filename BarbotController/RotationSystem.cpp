#include "RotationSystem.h"

RotationSystem::RotationSystem() {
    this->actIndex = 0;
    this->stepper = new StepperMotor(ROT_ENABLE,ROT_STEP,ROT_DIR);
    this->stepper->stepSpeed(1);
    pinMode(ENDSTOP_ROT,INPUT);
    digitalWrite(ENDSTOP_ROT,HIGH);
}

int RotationSystem::getActIndex() {
    return this->actIndex;
}

void RotationSystem::rotateTo(int index) {
    if (index < 0 || index >= BOTTLE_COUNT) {
    	return;
    }
    int diff = this->actIndex - index;
    if (diff < 0) {
        Serial.print("Go left ");
        this->stepper->setDirection(StepperMotor::LEFT);
        diff = diff * -1;
    } else {
        Serial.print("Go right ");
        this->stepper->setDirection(StepperMotor::RIGHT);
    }
    Serial.print(diff,DEC);
    Serial.println(" times");
    for (int i = 0; i < diff; i++) {
        stepper->step(ROT_ONE_UNIT);
        delay(1000);
    }
    this->actIndex = index;

}
void RotationSystem::setSpeed(int rpm) {
    this->stepper->setDirection(StepperMotor::RIGHT);
    Serial.print("Set rotation speed to ");
    Serial.print(rpm);
    Serial.println();
}

void RotationSystem::home() {
    this->stepper->setDirection(StepperMotor::LEFT);
    while (digitalRead(ENDSTOP_ROT) == 0) {
        this->stepper->step(200);       
    }
}




