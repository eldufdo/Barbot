#include "Arduino.h"
#include "SerialProcessor.h"

SerialProcessor::SerialProcessor(int baud,char *anim) {
    this->animation = anim;
    this->tmpAnimation = 0;
    Serial.begin(baud);
    cmdBuffer = "";
    drive = new DriveSystem();
    rot = new RotationSystem();
    initialized = false;
    this->state = 0;
    this->drive->down();
    this->rot->home();
    pinMode(ENDSTOP_GLAS,INPUT);
    digitalWrite(ENDSTOP_GLAS,HIGH);
}

void SerialProcessor::parseCmd() {
    int length = cmdBuffer.length();
    this->state = 0;
    char rotList[BUFFER_SIZE];
    char triggerList[BUFFER_SIZE];
    int index = 0;
    bool fFound = false;
    Serial.print("Cmdbuffer length: ");
    Serial.print(length,DEC);
    Serial.print(" --> ");
    Serial.print(cmdBuffer);
    Serial.println();
    for (int i = 0; i < length-1; i++) {
        char c = cmdBuffer[i];
        switch(state) {
            case 0:
                if (c == 'O') { // store EEPROM Drive Offset
                    Serial.println("Store Drive Offset");
                    state = 6;
                    break;
                }
                if (c == 'A') {
                    state = 5;
                    break;
                }
                if (c == 'L') {
                    state = 4;
                    break;
                }
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
	    case 4:
            if (c >= 48 && c <= 57) {
                c = c - 48;
            } 
            this->tmpAnimation = c;
            state = 0;
            return;
	    case 5:
            if (c >= 48 && c <= 57) {
                c = c - 48;
            } 
            *(this->animation) = c;
            state = 0;
            return;
        case 6:
            EEPROM.write(DRIVE_OFFSET_EEPROM_ADDR,c);
            int offset = DRIVE_OFFSET_MUL * c;
            Serial.print("Stored drive offset ");
            Serial.print(offset,DEC);
            Serial.println();
            drive->setOffset(offset);
            state = 0;
            return;
        }

    }
    Serial.print("busy\n");
    Serial.println("waiting for glas\n");
    *(this->animation) = 3;
    while (digitalRead(ENDSTOP_GLAS) == 0) {
    }
    Serial.println("got glas\n");
    *(this->animation) = this->tmpAnimation;
    for (int i = 0; i < index; i++) {
        rot->rotateTo(rotList[i]);
	int actTrigger = triggerList[i];
	if (actTrigger < 0 || actTrigger > 10) {
		break;
	}
        Serial.print("Trigger count: ");
        Serial.println(triggerList[i],DEC);
	for (int t=0; t < actTrigger; t++) {
		Serial.println("Trigger");
		if ( t == 0) {
            drive->fullUp();
		} else {
            drive->halfUp();
		}
		delay(2000);
        drive->halfDown();
		if (t > 0 && t < actTrigger - 1) {
			delay(500);
		}
	}
	drive->down();
    }
    rot->home();
    Serial.print("finished\n");
    Serial.println("take glas");
    *(this->animation) = 2;
    while (digitalRead(ENDSTOP_GLAS) == 1) {

    }
    delay(1000);
    Serial.print("ready\n");
    *(this->animation) = 4;
}

void SerialProcessor::read() {
    char c = Serial.read();
    cmdBuffer += c;
    if (c == '\r' || c == '\n') {
        this->parseCmd();
        cmdBuffer = "";
    }
}


void SerialProcessor::setDriveOffset(int offset) {
    this->drive->setOffset(offset);
}

void SerialProcessor::service() {
    if (initialized == false) {
    	if (Serial.available() > 0) {
	    char c = Serial.read();
	    switch (this->state) {
	    	case 0:
		    if (c == 'o') {
		    	this->state = 1;
		    }
		    break;
		case 1:
		    if (c == 'k') {
		    	this->state = 2;
		    } else {
		    	this->state = 0;
		    }
		    break;
		case 2:
		    if (c == '\n' || c == '\r') {
                Serial.print("ready\n");
			    *(this->animation) = 4;
			    initialized = true;
		    }
		    this->state = 0;
		    break;
	    }
	}
    } else {
   	 if (Serial.available() > 0) {
        	this->read();
    	}
    }
}
