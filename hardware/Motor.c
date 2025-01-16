#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Sensor.h"

void Motor_Init(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //启用 GPIO 时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);//启用TIM3 
	
	
	
    //配置 GPIO 引脚为推挽输出
    GPIO_InitTypeDef GPIOB_InitStructure;
    GPIOB_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;//12、13右轮，14、15左轮
    GPIOB_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  // 推挽输出
    GPIOB_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 输出速度 50MHz
    GPIO_Init(GPIOB, &GPIOB_InitStructure);
	
	GPIO_InitTypeDef GPIOA_InitStructure;
    GPIOA_InitStructure.GPIO_Pin = GPIO_Pin_6| GPIO_Pin_7;
    GPIOA_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  // 复用推挽输出
    GPIOA_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 输出速度 50MHz
    GPIO_Init(GPIOA, &GPIOA_InitStructure);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 1000 - 1; // 自动重装载值
    TIM_TimeBaseInitStructure.TIM_Prescaler = 700 - 1; // 预分频器
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	
    // 配置 TIM3 的通道 1 和 2 为 PWM 模式
    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;  // PWM 模式 1
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; // 使能输出
    TIM_OCInitStructure.TIM_Pulse = 0;  // 初始占空比为 0
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; // 高电平有效
    TIM_OC1Init(TIM3, &TIM_OCInitStructure); // 通道 1
    TIM_OC2Init(TIM3, &TIM_OCInitStructure); // 通道 2

    // 启动 TIM3
    TIM_Cmd(TIM3, ENABLE);
}

void LeftMotor_Run(uint16_t speed) {
	// 设置 PWM 占空比（速度）
    TIM_SetCompare1(TIM3, speed); 
	//电机1前进
    GPIO_SetBits(GPIOB, GPIO_Pin_13);  //  1 
    GPIO_ResetBits(GPIOB, GPIO_Pin_12); //  0 
}

void RightMotor_Run(uint16_t speed) {
	TIM_SetCompare2(TIM3, speed);  // 设置 TIM3 通道 2 的占空比
    //电机2前进
    GPIO_SetBits(GPIOB, GPIO_Pin_15);  // 1 
    GPIO_ResetBits(GPIOB, GPIO_Pin_14); // 0

}

void MotorLeft_Stop(void) {
    // 停止左电机
    TIM_SetCompare1(TIM3, 0);  // 占空比为 0
}

void MotorRight_Stop(void) {
    // 停止电机 2
    TIM_SetCompare2(TIM3, 0);  
}

/*****
void Run(void){
	Motor1_Run();
	Motor2_Run();
	
	if (Sensor4_Get() == 1 && Sensor1_Get() == 0){
		Motor2_Stop();
		Delay_ms(100); // 等待一段时间
		
	}
	else if(Sensor4_Get() == 0 && Sensor1_Get() == 1){
		Motor1_Stop ();
		Delay_ms(100); // 等待一段时间
	}
	else if(Sensor4_Get() == 1 && Sensor1_Get() == 1){
		Motor2_Stop();
		Motor1_Stop();
	}
	
}
*****/
