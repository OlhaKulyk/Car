#include "ProximitySensors.h"

static uint8_t proximitySensors[5];

void ProximitySensors_Init()
{
	InitSharp();
	
  VL53L0X_Initialize();	
  delay_ms(10);
	GPIO_SetBits(GPIOA, GPIO_Pin_12 | GPIO_Pin_15);
	delay_ms(10);
	GPIO_ResetBits(GPIOA, GPIO_Pin_12);
	
	VL53L0X.address = 0x52;
	VL53L0X_readReg(IDENTIFICATION_REVISION_ID);
	VL53L0X_setAddress((uint8_t)0x29);
	delay_ms(100);
	VL53L0X_init(true);
	delay_ms(100);
	VL53L0X_readReg(IDENTIFICATION_REVISION_ID);
	VL53L0X_setTimeout(500);
	VL53L0X_setMeasurementTimingBudget(20000);
	delay_ms(100);
	VL53L0X_startContinuous(0);
	GPIO_SetBits(GPIOA, GPIO_Pin_12);
	delay_ms(100);
	VL53L0X.address = 0x52;
	VL53L0X_init(true);
	delay_ms(100);
	VL53L0X_setTimeout(500);
	VL53L0X_setMeasurementTimingBudget(20000);
	delay_ms(100);
	VL53L0X_startContinuous(0);
}

void ProximitySensors_Read()
{
	readSharp(proximitySensors);
	*(proximitySensors+1) = Read_from_One((uint8_t)0x29)/10;
	if(*(proximitySensors+1) > 150)
		*(proximitySensors+1) = 150;
	*(proximitySensors+3) = Read_from_One((uint8_t)0x52)/10;
		if(*(proximitySensors+3) > 150)
		*(proximitySensors+3) = 150;	
}

uint8_t GetSensor_Data(uint8_t sensor)
{
	if(sensor <= 4)
		return proximitySensors[sensor];
	return 0;
}
