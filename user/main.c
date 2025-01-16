#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "Delay.h"
#include "key.h"
#include "Sensor.h"
#include "Motor.h"

#define HIGH 600
#define MIDDLE 500
#define LOW 200

uint8_t KeyNum = 0;

int main(void){

	LED_Init();
	Key_Init();
	Sensor_Init();
	Motor_Init();
	
	LED3_OFF();
    LED4_OFF();
    LED5_OFF();
	
	while(1){
		Key_GetNum(&KeyNum);
		if (KeyNum == 1){
			LED3_ON();
		}
		else {
			LED3_OFF();
			LED4_OFF();
			LED5_OFF();
			MotorLeft_Stop();
			MotorRight_Stop();					
			while(KeyNum != 1){
				Key_GetNum(&KeyNum);
			}
		}
		
		if(SensorLeft_Get() == 0 && SensorRight_Get() == 0){
			LED4_OFF();
			LED5_OFF();
			LeftMotor_Run (MIDDLE);
			RightMotor_Run (MIDDLE);
		}
		
		if(SensorLeft_Get() == 1 && SensorRight_Get() == 1){
			LED4_ON();
            		LED5_ON(); 
			//LeftMotor_Run(MIDDLE);
			//RightMotor_Run(MIDDLE);
			/***
			while(SensorLeft_Get() == 1 && SensorRight_Get() == 1){
				MotorLeft_Stop();
				MotorRight_Stop();
				Key_GetNum(&KeyNum);
				
				if (KeyNum != 1)
					break;
			}
			***/
		}
		
		if (SensorLeft_Get() == 1 && SensorRight_Get() == 0) {  // 假设 Sensor1_Get() 返回 1 表示识别到黑线
            		LED4_ON();  // 左侧传感器识别到黑线，LED亮起
			LED5_OFF();
			//RightMotor_Run(HIGH);
			//LeftMotor_Run (LOW);
			MotorLeft_Stop();
			
        } 

        // 检测右侧传感器状态
        if (SensorLeft_Get() == 0 && SensorRight_Get() == 1) {  // 假设 Sensor4_Get() 返回 1 表示识别到黑线
			LED4_OFF();
            		LED5_ON();  // 右侧传感器识别到黑线，LED 亮起
			//LeftMotor_Run(HIGH);
			//RightMotor_Run (LOW);
			MotorRight_Stop();
			
        } 
		
    }    
}

