#include "stm32f10x.h"
#include "Settings.h"
#include "ProximitySensors.h"
#include "Engine.h"
#include "Servo.h"
#include "RPConnection.h"

uint8_t times = 0;

void TIMTransmit_IRQ_Init()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
	TIM_TimeBaseInitTypeDef TIM_TimeBase;
	
	TIM_TimeBase.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBase.TIM_Prescaler = 7200;
	TIM_TimeBase.TIM_Period = 100;
	TIM_TimeBase.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBase.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBase);
	
  TIM_Cmd(TIM2, ENABLE);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	NVIC_InitTypeDef nvicStructure;
  nvicStructure.NVIC_IRQChannel = TIM2_IRQn;
  nvicStructure.NVIC_IRQChannelPreemptionPriority = 0;
  nvicStructure.NVIC_IRQChannelSubPriority = 1;
  nvicStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&nvicStructure);
	
}
//10ms
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update)){
		ProximitySensors_Read();
		if(times < 4){
			times++;
		}else{
			times = 0;
			ChangeSpeed(getNeededSpeed());
		}
		if(GetAngle() != getNeededAngle())
			ChangeAngle(getNeededAngle());
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}

int main(void)
{
	SetSysClockTo72();
	SysTick_setting();
	
  ProximitySensors_Init();
	OptronInit();
	EngineInit();
	ServoInit();
	
	RPConnection_Init();
	TIMTransmit_IRQ_Init();
	while(1){};	
}
