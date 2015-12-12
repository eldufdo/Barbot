#include "RotationSystem.h"

RotationSystem::RotationSystem() {
    this->actIndex = 0;
    this->stepper = new StepperMotor(ROT_ENABLE,ROT_STEP,ROT_DIR);
    pinMode(ENDSTOP_ROT,INPUT);
    pinMode(ROT_ENABLE,OUTPUT);
    pinMode(ROT_DIR,OUTPUT);
    pinMode(ROT_STEP,OUTPUT);
    digitalWrite(ROT_ENABLE,LOW);
}

void RotationSystem::rotateTo(int index) {
    int diff = this->actIndex - index;
    if (diff < 0) {
        Serial.print("Go left ");
        setDirection(LEFT);
        diff = diff * -1;
    } else {
        Serial.print("Go right ");
        setDirection(RIGHT);
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
    Serial.print("Set rotation speed to ");
    Serial.print(rpm);
    Serial.println();
}

void RotationSystem::home() {
    //while (digitalRead(ENDSTOP_ROT) == 0) {
        //this->stepper.step(200);       
    //}
}



void RotationSystem::setDirection(Direction dir) {
    if (dir == LEFT) {
    #if ROT_INVERT == 0
        digitalWrite(ROT_DIR,LOW);
    #else
        digitalWrite(ROT_DIR,HIGH);
    #endif
    } else {
        #if ROT_INVERT == 0
            digitalWrite(ROT_DIR,HIGH);
        #else
            digitalWrite(ROT_DIR,LOW);
        #endif

    }
}
