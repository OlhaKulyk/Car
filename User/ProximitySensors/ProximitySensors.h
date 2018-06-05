#ifndef PROXIMITY_SENSORS_H
#define PROXIMITY_SENSORS_H

#include "Sharp.h"
#include "VL53L0X_Initialize.h"

void ProximitySensors_Init(void);
void ProximitySensors_Read(void);

uint8_t GetSensor_Data(uint8_t sensor);

#endif /* PROXIMITY_SENSORS_H */
