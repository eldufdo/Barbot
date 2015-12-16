#ifndef ROTATION_H
#define ROTATION_H

#include "Arduino.h"
#include "pin.h"
#include "StepperMotor.h"

class RotationSystem {
    private:
        StepperMotor *stepper;
        int actIndex;
    public:
        RotationSystem();
        void rotateTo(int index);
        void setSpeed(int rpm);
        void home();
	int getActIndex();
};

#endif
