#ifndef DRIVE_H
#define DRIVE_H

#include "Arduino.h"

class DriveSystem {
    enum Position {IN,OUT};

    private:
        Position actPosition;
    public:
        DriveSystem();
        void in();
        void out();
};
#endif
