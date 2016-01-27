#ifndef STEPPERMOTOR_H
#define STEPPERMOTOR_H

#include "Arduino.h"
#include "pin.h"

class StepperMotor {
    private:
        char stepPin;
        char enablePin;
        char dirPin;
	int speed;
    public:
    enum Direction {LEFT,RIGHT};
    StepperMotor(char enablePin,char stepPin,char dirPin);
	void setDirection(Direction dir);
    void stepAccel(int steps);
    void step(int steps);
	void stepSpeed(int speed);
};

#endif
