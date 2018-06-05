#include "Servo.h"
#include "PID.h"

void ServoInit()
{
	GPIO_InitTypeDef port;
  TIM_TimeBaseInitTypeDef timer;
  TIM_OCInitTypeDef timerPWM;
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  
  port.GPIO_Mode = GPIO_Mode_AF_PP;
  port.GPIO_Pin = GPIO_Pin_11;
  port.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &port);
	
	TIM_TimeBaseStructInit(&timer);
  timer.TIM_Prescaler = 1440-1;
  timer.TIM_Period = 1000; 
  timer.TIM_ClockDivision =  TIM_CKD_DIV1;
  timer.TIM_CounterMode = TIM_CounterMode_Up;
	timer.TIM_RepetitionCounter = 0;
	
  TIM_TimeBaseInit(TIM1, &timer);
 
  TIM_OCStructInit(&timerPWM);
  timerPWM.TIM_Pulse = 50;
  timerPWM.TIM_OCMode = TIM_OCMode_PWM1;
  timerPWM.TIM_OutputState = TIM_OutputState_Enable;
	timerPWM.TIM_OutputNState = TIM_OutputNState_Enable;
  timerPWM.TIM_OCPolarity = TIM_OCPolarity_High;
	timerPWM.TIM_OCNPolarity = TIM_OCNPolarity_High ;
	timerPWM.TIM_OCIdleState = TIM_OCIdleState_Set;
	timerPWM.TIM_OCNIdleState = TIM_OCIdleState_Set;
  
	TIM_OC4Init(TIM1,&timerPWM);
  TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);

	TIM_CtrlPWMOutputs(TIM1, ENABLE);
  TIM_Cmd(TIM1, ENABLE);
	TIM_SetCompare4(TIM1, 75);
}

// pwm 63 - 87
// angle -12 - +12
signed int GetAngle()
{
	return TIM_GetCapture4(TIM1)-75;
}

static uint8_t AngletoPWM(uint8_t Angle)
{
	return (uint8_t)Angle+75;
}

void ChangeAngle(signed int angle)
{
	TIM_SetCompare4(TIM1, AngletoPWM(angle));
}
