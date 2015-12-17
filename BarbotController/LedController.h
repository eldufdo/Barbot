#ifndef LEDCONTROLLER_H
#define LEDCONTROLLER_H

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>

class LedController{
    public:
	LedController();
	void stop();
	void start(int index);
	enum Animation {KNIGHT_RIDER,RAINBOW,FADE_IN_OUT};
};
#endif
