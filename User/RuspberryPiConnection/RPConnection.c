#include "RPConnection.h"
#include "ProximitySensors.h"

static uint8_t next = 0;
static uint8_t data = 0;

static uint8_t angle = 0;
static uint8_t speed = 0;

void RPConnection_Init()
{
	GPIO_InitTypeDef spiGPIO;
	GPIO_InitTypeDef SSspiGPIO;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	spiGPIO.GPIO_Pin =  GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	spiGPIO.GPIO_Mode = GPIO_Mode_AF_PP;
	spiGPIO.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&spiGPIO);
	
	SSspiGPIO.GPIO_Pin =  GPIO_Pin_12;
	SSspiGPIO.GPIO_Mode = GPIO_Mode_IN_FLOATING ;
	SSspiGPIO.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&SSspiGPIO);
	
	SPI_InitTypeDef spi;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2 ,ENABLE);
	
	spi.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	spi.SPI_Mode = SPI_Mode_Slave;
	spi.SPI_DataSize = SPI_DataSize_8b;
	spi.SPI_CPOL = SPI_CPOL_Low;
	spi.SPI_CPHA = SPI_CPHA_1Edge;
	spi.SPI_NSS = SPI_NSS_Soft;
	spi.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
	spi.SPI_FirstBit = SPI_FirstBit_MSB;
	spi.SPI_CRCPolynomial = 7;
	
	SPI_Init(SPI2, &spi);
	SPI_I2S_ITConfig(SPI2, SPI_I2S_IT_RXNE , ENABLE);
	
	NVIC_InitTypeDef nvicStructure;
  nvicStructure.NVIC_IRQChannel = SPI2_IRQn;
  nvicStructure.NVIC_IRQChannelPreemptionPriority = 0;
  nvicStructure.NVIC_IRQChannelSubPriority = 1;
  nvicStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&nvicStructure);
	
	SPI_Cmd(SPI2, ENABLE);
}

void SPI2_IRQHandler(void)
{
	if (SPI_I2S_GetITStatus(SPI2, SPI_I2S_IT_RXNE)){

		while (SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_BSY)!=RESET);
		data = SPI_I2S_ReceiveData(SPI2);
		if(data == 1 || data == 2)
			next = data;
		else {
			if(next == 1)
				speed = data;
			else if(next == 2)
				angle = data;
			next = 0;
		}
		data = 0;
		SPI_I2S_ClearITPendingBit(SPI2, SPI_I2S_IT_RXNE);
	}
}

signed int getNeededAngle()
{
	return angle-12;
}

signed int getNeededSpeed()
{
	return speed-150;
}
