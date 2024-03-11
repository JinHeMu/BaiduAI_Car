#ifndef __PID_H__
#define __PID_H__


#include "headfile.h"

/******************************************************************************/
#define VV_DEADLINE 		    2						//速度PID，设置死区范围，消抖，静止强硬程度
#define PID_KP					1.6f					//PID标定值
#define PID_KI					0.5f					//PID标定值
#define PID_KD					0.02f					//PID标定值

/**
* @brief    PID相关
**/
typedef struct 
{
	float Speed_Input;        	            //速度PID，速度设定值
	float Speed_FeedBack;                  //速度PID，速度反馈值
    float Speed_Now_Error;	 	            //速度PID，速度误差,vi_Ref - vi_FeedBack
	float Speed_Pre_Error; 	            //速度PID，前一次，速度误差之差，d_error-PreDerror;
	float Kp;	 		 			    //比例系数，Kp = Kp
	float Ki;		 				    //积分系数，Ki = Kp * ( T / Ti )
	float Kd;		 				    //微分系数，Kd = KP * Td * T
	float Speed_Output; 				        //PID输出值
}PIDStruct;

extern PIDStruct pidStr;

void PID_Init(void);
signed int PID_MoveCalculate(PIDStruct *pp);
int Incremental_pid(int Target, int Encoder);

#endif



