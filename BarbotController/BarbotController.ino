#include "pin.h"
#include "Arduino.h"
#include "SerialProcessor.h"
#include "PressureSensor.h"
#include <TimerOne.h>
#include <Adafruit_NeoPixel.h>

SerialProcessor *serial;

#define DEBUG 0


Adafruit_NeoPixel *strip;
 

char animation = 0;
int animationIndex = 0;
int animationState = 0;

int randomCounter = 0;
void randomPixel() {
	randomCounter++;
	if (randomCounter == 64) {
		for (int i = 0; i < LED_COUNT; i++) {
			strip->setPixelColor(i,random(255),random(255),random(255));
		}
		strip->show();
		randomCounter = 0;
	}
}


int brightness = 0;   
int fadeState = 0;
void fade(char r, char g, char b) {
	for (int i = 0; i < LED_COUNT; i++) {
		if (r > 0) {
			r = brightness;
		}
		if (g > 0) {
			g = brightness;
		}
		if (b > 0) {
			b = brightness;
		}
		strip->setPixelColor(i,r,g,b);
	}
	if (fadeState == 0) {
	    brightness++;
	    if (brightness == 255) {
		fadeState = 1;
	    }
	} else {
	    brightness--;
	    if (brightness == 0) {
		fadeState = 0;
	    }
	}
	strip->show();
	
}

int hcounter = 0;
int hscounter = 0;
int hstate = 0;
int hmax = 200;
int flashcounter = 0;
void hellsbells() {
	switch (hstate) {
		case 0:
			hscounter++;
			if (hscounter >= hmax) {
				hcounter++;
				hscounter = 0;
			}
			if (hcounter == 1) {
				hcounter++;
				hstate = 1;
			}
			break;	
		case 1:	
			for (int i = 0; i < LED_COUNT; i++) {
				strip->setPixelColor(i,128,128,128);		
			}
			strip->show();
			hstate = 2;
			break;
		case 2:
			hscounter++;
			if (hscounter == 50) {
				hscounter = 0;
				hcounter = 0;
				strip->clear();
				strip->show();
				hstate = 0;
				if (flashcounter == 0) {
					hmax = 950;
					flashcounter++;
				} else if (flashcounter == 1) {
					hmax = 800;
					flashcounter++;
				} else if (flashcounter == 2) {
					animation = 2;
					hcounter = 0;
					hscounter = 0;
					hmax = 200;
					flashcounter = 0;
				}
			}
			break;
		case 3:
			
			break;
		case 4:
			break;	
	}
}


int kpos=0;
int kState = 0;
int kCounter = 0;

void knightrider() {
	kCounter++;
	if (kCounter < 20) {
		return;
	}	
	kCounter = 0;
	strip->clear();
	for (int i = 0; i < 4; i++) {
		strip->setPixelColor(12 - kpos - 1,15,0,0);
		strip->setPixelColor(12 - kpos - 2,64,0,0);
		strip->setPixelColor(12 - kpos - 3,255,0,0);
		strip->setPixelColor(12 - kpos - 4,64,0,0);
		strip->setPixelColor(12 - kpos - 5,15,0,0);

		strip->setPixelColor(kpos+12,15,0,0);
		strip->setPixelColor(kpos+13,64,0,0);
		strip->setPixelColor(kpos+14,255,0,0);
		strip->setPixelColor(kpos+15,64,0,0);
		strip->setPixelColor(kpos+16,15,0,0);
	}
	if (kState == 0) {
		kpos++;
	} else {
		kpos--;
	}
	if (kpos == 12 - 5) {
		kState = 1;
	}
	if (kpos == 0) {
		kState = 0;
	}
	strip->show();
}

void ledCallback(void) {
	switch (animation) {
		case 1:
			knightrider();
			break;
		case 2: 
			fade(1,0,0);
			break;
		case 3: 
			fade(1,1,0);
			break;
		case 4: 
			fade(0,1,0);
			break;
		case 5:
			randomPixel();
			break;
		case 6:
			hellsbells();
			break;
		default: 
			strip->clear();
			strip->show();
			return;
	}
}

void setup() {
    pinMode(LED_PIN,OUTPUT);
    serial = new SerialProcessor(9600,&animation);
    pinMode(ROT_ENABLE,OUTPUT);
    pinMode(ROT_DIR,OUTPUT);
    pinMode(ROT_STEP,OUTPUT);
    digitalWrite(ROT_ENABLE,LOW);
    digitalWrite(ROT_DIR,HIGH);
    Serial.println("Barbot");
    strip = new Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
    strip->begin();
    strip->setBrightness(64);
    strip->show(); // Initialize all pixels to 'off'
    randomSeed(0);
    Timer1.initialize(5000);  
    Timer1.attachInterrupt(ledCallback);
}



#if DEBUG == 1
RotationSystem *rot = new RotationSystem();
DriveSystem *drive = new DriveSystem();
#endif
	
void loop() {
#if DEBUG == 0
    serial->service();
#else
    if (Serial.available() > 0) {
	if (Serial.available()) {
	    char c = Serial.read();
	    if (c == 'u') {
		drive->up(3000);
	    } else if (c == 'd') {
		drive->down();
	    } else if (c == 'l') {
		rot->rotateTo(rot->getActIndex()+1);
	    } else if (c == 'r') {
		rot->rotateTo(rot->getActIndex()-1);
	    } else if (c == 'h') {
		rot->home();
	    } else if (c == 't') {
		drive->up(30000);
		drive->up(30000);
		drive->down();
	    }
	}
		
    }
    Serial.print("Rot home: ");
    Serial.print(digitalRead(ENDSTOP_ROT));
    Serial.print("Drive home: ");
    Serial.print(digitalRead(DRIVE_ENDSTOP_PIN));
    Serial.print("Glas triggered: ");
    Serial.print(digitalRead(ENDSTOP_GLAS));
    Serial.println();
    delay(200);
#endif
}
