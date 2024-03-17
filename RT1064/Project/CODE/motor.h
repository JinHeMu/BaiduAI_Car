#ifndef __MOTOR_H__
#define __MOTOR_H__

/*-----------------------------------------  I N C L U D E S  -----------------------------------------*/
#include "headfile.h"

/*---------------------------------------  D E F I N I T I O N  ---------------------------------------*/

#define MOTOR_DIR D2
#define MOTOR_PWM PWM1_MODULE3_CHA_D0
#define MOTOR_FREQ 12000

#define  MOTOR_PWM_MAX   			4000		
#define  MOTOR_PWM_MIN			    -4000		
#define  MOTOR_SPEED_MAX		    10.0f	 	//电机最大转速(m/s) (0.017,8.04)
#define  MOTOR_CONTROL_CYCLE	    0.01f    	//电机控制周期T：10ms

/**
* @brief    电机相关
**/
typedef struct 
{
	float ReductionRatio ;					    //电机减速比
	float EncoderLine ; 						//编码器线数=光栅数16*4
	signed int EncoderValue;				    //编码器实时速度
	float DiameterWheel;						//轮子直径：mm
	bool CloseLoop;							    //开环模式
	uint16_t Counter;							//线程计数器
}MotorStruct;


extern MotorStruct motorStr;


void MOTOR_Init(void);
void MOTOR_SetPwmValue(signed int pwm);
void MOTOR_ControlLoop(float speed);


//===========================================  End Of File  ===========================================//
#endif


