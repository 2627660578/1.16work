#ifndef __MOTOR_H
#define __MOTOR_H

void Motor_Init(void);
void LeftMotor_Run(uint16_t speed);
void RightMotor_Run(uint16_t speed);
void MotorLeft_Stop(void);
void MotorRight_Stop(void);
void Run(void);
#endif
