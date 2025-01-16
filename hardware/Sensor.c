#include "stm32f10x.h"                  // Device header

void Sensor_Init(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure4;
	GPIO_InitStructure4.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure4.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure4.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure4);
	
	GPIO_InitTypeDef GPIO_InitStructure1;
	GPIO_InitStructure1.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure1.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure1.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure1);
}

uint8_t SensorLeft_Get(void){
	return GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4);
}

uint8_t SensorRight_Get(void){
	return GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1);
}
