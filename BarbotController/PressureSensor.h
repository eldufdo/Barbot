#ifndef PRESSURE_H
#define PRESSURE_H

#include "Arduino.h"
#include "pin.h"

class PressureSensor {

    private:
    public:
        PressureSensor();
	int getPressureValue();
};
#endif
