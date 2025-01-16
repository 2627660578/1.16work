#include "stm32f10x.h"                  // Device header
#include "Delay.h"

void Key_Init(void){
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOB ,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructureB;
	GPIO_InitStructureB.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructureB.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructureB.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructureB);
	
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOA ,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructureA;
	GPIO_InitStructureA.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructureA.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructureA.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructureA);
}

uint8_t Key_GetNum(uint8_t *KeyNum){
	
	if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7) == 0){
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7) == 0);
		Delay_ms(20);
		*KeyNum = 1;
	}
	if (GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8) == 0){
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8) == 0);	
		Delay_ms(20);
		*KeyNum = 2;
	}
}

