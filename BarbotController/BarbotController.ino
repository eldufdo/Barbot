#include "pin.h"
#include "Arduino.h"
#include "SerialProcessor.h"
SerialProcessor *serial;
bool raspiActive = false;

void setup() {
    pinMode(LED_PIN,OUTPUT);
    serial = new SerialProcessor(9600);
    pinMode(ROT_ENABLE,OUTPUT);
    pinMode(ROT_DIR,OUTPUT);
    pinMode(ROT_STEP,OUTPUT);
    digitalWrite(ROT_ENABLE,LOW);
    digitalWrite(ROT_DIR,HIGH);
    Serial.println("Barbot");
}

void loop() {
    serial->service();
}
