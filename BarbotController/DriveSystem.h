#ifndef DRIVE_H
#define DRIVE_H

#include "Arduino.h"
#include "StepperMotor.h"


class DriveSystem {
    enum Position {IN,OUT};

    private:
        Position actPosition;
	StepperMotor *stepper;
    public:
        DriveSystem();
        void up(int step);
        void down();
        void down(int step);
};
#endif
