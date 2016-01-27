#ifndef SERIALPROCESSOR_H
#define SERIALPROCESSOR_H

#include "DriveSystem.h"
#include "RotationSystem.h"
#include "pin.h"

class SerialProcessor {
    private:
        void read();
        void parseCmd();
        String cmdBuffer;
        DriveSystem *drive;
        RotationSystem *rot;
	bool initialized;
	int state;
	char *animation;
	char tmpAnimation;
    public:
        SerialProcessor(int baud,char *animation);
        void service();
};
#endif
