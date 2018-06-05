#ifndef ENGINE_H
#define ENGINE_H

#include "stm32f10x.h"

#define Engine_Kp 0.09
#define Engine_Ki 0.05
#define Engine_Kd 0.1

void OptronInit(void);
void EngineInit(void);

void ChangeSpeed(signed int speedNeed);

#endif /* ENGINE_H */
