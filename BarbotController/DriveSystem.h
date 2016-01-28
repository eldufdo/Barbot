#ifndef DRIVE_H
#define DRIVE_H

#include "Arduino.h"
#include "StepperMotor.h"


class DriveSystem {
    enum Position {IN,OUT};

    private:
        Position actPosition;
        StepperMotor *stepper;
        int offset;
    public:
        DriveSystem();
        void up(int step);
        void fullUp();
        void halfUp();
        void halfDown();
        void down();
        void down(int step);
        void setOffset(int offset);
};
#endif
