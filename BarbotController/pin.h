#ifndef PIN_H
#define PIN_H

#define BUFFER_SIZE 20

#define ROT_STEP 3
#define ROT_DIR 6
#define ROT_ENABLE 8
#define ROT_MICROSTEPS 16
#define ROT_INVERT 0
#define ROT_STEPS 200 * ROT_MICROSTEPS
#define ROT_ONE_UNIT 1765

#define DRIVE_STEP 2
#define DRIVE_DIR 5
#define DRIVE_ENABLE 8
#define DRIVE_MICROSTEPS 16
#define DRIVE_STEPS 200 * DRIVE_MICROSTEPS
#define DRIVE_OFFSET_DEFAULT 0
#define DRIVE_OFFSET_MUL 40

#define EEPROM_MAGIC 0xCD
#define DRIVE_OFFSET_EEPROM_ADDR 1


#define DRIVE_UNIT_1CL 200
#define DRIVE_UNIT_2CL 300
#define DRIVE_UNIT_3CL 400
#define DRIVE_UNIT_4CL 500

#define TRIGGER_PIN 7

#define LED_PIN 13

#define LED_COUNT 24
#define ENDSTOP_GLAS 4
#define ENDSTOP_ROT 12

#define DRIVE_ENDSTOP_PIN 7

#define PRESSURE_PIN A4

#define BOTTLE_COUNT 6

#define PIXEL_COUNT 16
#define PIXEL_PIN 4
#endif
