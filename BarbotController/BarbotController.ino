#include "pin.h"
#include "Arduino.h"
#include "SerialProcessor.h"
#include "PressureSensor.h"
#include <TimerOne.h>
SerialProcessor *serial;
PressureSensor *pressure;

#define DEBUG 1


void setup() {
    pinMode(LED_PIN,OUTPUT);
    serial = new SerialProcessor(9600);
    pinMode(ROT_ENABLE,OUTPUT);
    pinMode(ROT_DIR,OUTPUT);
    pinMode(ROT_STEP,OUTPUT);
    digitalWrite(ROT_ENABLE,LOW);
    digitalWrite(ROT_DIR,HIGH);
    Serial.println("Barbot");
    pressure = new PressureSensor();
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
		drive->up(1000);
	    } else if (c == 'd') {
		drive->down();
	    } else if (c == 'l') {
		rot->rotateTo(rot->getActIndex()+1);
	    } else if (c == 'r') {
		rot->rotateTo(rot->getActIndex()-1);
	    }
	}
		
    }
    Serial.print("Pressure: ");
    Serial.print(pressure->getPressureValue(),DEC);
    Serial.print("Rot home: ");
    Serial.print(digitalRead(ENDSTOP_ROT));
    Serial.print("Drive home: ");
    Serial.print(digitalRead(DRIVE_ENDSTOP_PIN));
    Serial.println();
    delay(200);
#endif
}
