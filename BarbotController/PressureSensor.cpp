#include "PressureSensor.h"

PressureSensor::PressureSensor() {

}
 
int PressureSensor::getPressureValue() {
    return analogRead(PRESSURE_PIN);
}
