#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Sensor.h"

void Motor_Init(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //���� GPIO ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);//����TIM3 
	
	
	
    //���� GPIO ����Ϊ�������
    GPIO_InitTypeDef GPIOB_InitStructure;
    GPIOB_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;//12��13���֣�14��15����
    GPIOB_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  // �������
    GPIOB_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // ����ٶ� 50MHz
    GPIO_Init(GPIOB, &GPIOB_InitStructure);
	
	GPIO_InitTypeDef GPIOA_InitStructure;
    GPIOA_InitStructure.GPIO_Pin = GPIO_Pin_6| GPIO_Pin_7;
    GPIOA_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  // �����������
    GPIOA_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // ����ٶ� 50MHz
    GPIO_Init(GPIOA, &GPIOA_InitStructure);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 1000 - 1; // �Զ���װ��ֵ
    TIM_TimeBaseInitStructure.TIM_Prescaler = 700 - 1; // Ԥ��Ƶ��
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	
    // ���� TIM3 ��ͨ�� 1 �� 2 Ϊ PWM ģʽ
    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;  // PWM ģʽ 1
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; // ʹ�����
    TIM_OCInitStructure.TIM_Pulse = 0;  // ��ʼռ�ձ�Ϊ 0
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; // �ߵ�ƽ��Ч
    TIM_OC1Init(TIM3, &TIM_OCInitStructure); // ͨ�� 1
    TIM_OC2Init(TIM3, &TIM_OCInitStructure); // ͨ�� 2

    // ���� TIM3
    TIM_Cmd(TIM3, ENABLE);
}

void LeftMotor_Run(uint16_t speed) {
	// ���� PWM ռ�ձȣ��ٶȣ�
    TIM_SetCompare1(TIM3, speed); 
	//���1ǰ��
    GPIO_SetBits(GPIOB, GPIO_Pin_13);  //  1 
    GPIO_ResetBits(GPIOB, GPIO_Pin_12); //  0 
}

void RightMotor_Run(uint16_t speed) {
	TIM_SetCompare2(TIM3, speed);  // ���� TIM3 ͨ�� 2 ��ռ�ձ�
    //���2ǰ��
    GPIO_SetBits(GPIOB, GPIO_Pin_15);  // 1 
    GPIO_ResetBits(GPIOB, GPIO_Pin_14); // 0

}

void MotorLeft_Stop(void) {
    // ֹͣ����
    TIM_SetCompare1(TIM3, 0);  // ռ�ձ�Ϊ 0
}

void MotorRight_Stop(void) {
    // ֹͣ��� 2
    TIM_SetCompare2(TIM3, 0);  
}

/*****
void Run(void){
	Motor1_Run();
	Motor2_Run();
	
	if (Sensor4_Get() == 1 && Sensor1_Get() == 0){
		Motor2_Stop();
		Delay_ms(100); // �ȴ�һ��ʱ��
		
	}
	else if(Sensor4_Get() == 0 && Sensor1_Get() == 1){
		Motor1_Stop ();
		Delay_ms(100); // �ȴ�һ��ʱ��
	}
	else if(Sensor4_Get() == 1 && Sensor1_Get() == 1){
		Motor2_Stop();
		Motor1_Stop();
	}
	
}
*****/
