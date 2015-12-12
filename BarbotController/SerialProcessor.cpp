#include "SerialProcessor.h"

SerialProcessor::SerialProcessor(int baud) {
    Serial.begin(baud);
    cmdBuffer = "";
    drive = new DriveSystem();
    rot = new RotationSystem();
}

void SerialProcessor::parseCmd() {
    Serial.println("Parse cmd");
    int length = cmdBuffer.length();
    int state = 0;
    char rotList[BUFFER_SIZE];
    char triggerList[BUFFER_SIZE];
    char index = 0;
    bool fFound = false;
    for (int i = 0; i < length-1; i++) {
        char c = cmdBuffer[i];
        switch(state) {
            case 0:
                if (c != 'F' && c != ' ') {
                    Serial.print("Error: unexpected char: ");
                    Serial.println(c,DEC);
                    return;
                }
                if (c == 'F') {
                    state = 1;
                }
                break;
            case 1:
                if (c >= 48 && c <= 57) {
                       c = c - 48;
                } else {
                    Serial.println("Invalid F parameter");
                    return;
                }
                rotList[index] = c;
                fFound = true;
                state = 2;
                break;
            case 2:
                if (c != ' ') {
                    Serial.println("Parsing error: no space after F cmd");
                    return;
                }
                state = 3;
                break;
            case 3:
                if (c >= 48 && c <= 57) {
                       c = c - 48;
                } else {
                    Serial.println("Invalid trigger parameter");
                    return;
                }
                if (fFound == false) {
                    Serial.println("Error no F cmd for trigger parameter");
                    return;
                }
                triggerList[index] = c;
                index++;
                if (index >= BUFFER_SIZE) {
                    Serial.println("Cmd Buffer overflow!");
                    return;
                }
                fFound = false;
                state = 0;
                break;
        }
    }
    for (int i = 0; i < index; i++) {
        rot->rotateTo(rotList[i]);
        Serial.print("Trigger count: ");
        Serial.println(triggerList[i],DEC);
    }
}

void SerialProcessor::read() {
    char c = Serial.read();
    cmdBuffer += c;
    if (c == '\r' || c == '\n') {
        this->parseCmd();
        cmdBuffer = "";
    }
}

void SerialProcessor::service() {
    if (Serial.available() > 0) {
        this->read();
    }
}
