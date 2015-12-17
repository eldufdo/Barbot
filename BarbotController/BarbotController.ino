#include "pin.h"
#include "Arduino.h"
#include "SerialProcessor.h"
#include "PressureSensor.h"
#include <TimerOne.h>
#include <Adafruit_NeoPixel.h>

SerialProcessor *serial;

#define DEBUG 0


Adafruit_NeoPixel *strip;
    

void setup() {
    pinMode(LED_PIN,OUTPUT);
    serial = new SerialProcessor(9600);
    pinMode(ROT_ENABLE,OUTPUT);
    pinMode(ROT_DIR,OUTPUT);
    pinMode(ROT_STEP,OUTPUT);
    digitalWrite(ROT_ENABLE,LOW);
    digitalWrite(ROT_DIR,HIGH);
    Serial.println("Barbot");
    strip = new Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
    strip->begin();
    strip->setBrightness(64);
    for (int i = 0; i < LED_COUNT; i++) { 
	strip->setPixelColor(i,200,0,0);
    }
    strip->show(); // Initialize all pixels to 'off'
    
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
