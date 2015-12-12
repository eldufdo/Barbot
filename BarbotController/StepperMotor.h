#ifndef STEPPERMOTOR_H
#define STEPPERMOTOR_H

#include "Arduino.h"
#include "pin.h"

class StepperMotor {
    private:
        enum Direction {LEFT,RIGHT};
        char stepPin;
        char enablePin;
        char dirPin;
    public:
        StepperMotor(char enablePin,char stepPin,char dirPin);
        void step(int steps);
};

#endif
