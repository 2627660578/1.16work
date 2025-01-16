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
		
		if (SensorLeft_Get() == 1 && SensorRight_Get() == 0) {  // ���� Sensor1_Get() ���� 1 ��ʾʶ�𵽺���
            LED4_ON();  // ��ഫ����ʶ�𵽺��ߣ�LED����
			LED5_OFF();
			//RightMotor_Run(HIGH);
			LeftMotor_Run (LOW);
			MotorLeft_Stop();
			
        } 

        // ����Ҳഫ����״̬
        if (SensorLeft_Get() == 0 && SensorRight_Get() == 1) {  // ���� Sensor4_Get() ���� 1 ��ʾʶ�𵽺���
			LED4_OFF();
            LED5_ON();  // �Ҳഫ����ʶ�𵽺��ߣ�LED ����
			//LeftMotor_Run(HIGH);
			RightMotor_Run (LOW);
			MotorRight_Stop();
			
        } 
		
    }    
}

