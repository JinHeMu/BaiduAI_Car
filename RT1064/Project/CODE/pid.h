#ifndef __PID_H__
#define __PID_H__


#include "headfile.h"

/******************************************************************************/
#define PID_KP					150.0f					//PID标定值
#define PID_KI					1.5f					//PID标定值
#define PID_KD					0.0f					//PID标定值

/**
* @brief    PID相关
**/
typedef struct 
{
	float Speed_Target;        	            //速度PID，速度设定值
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
int Incremental_pid1(int Target, int Encoder);
signed int PID_MoveCalculate(PIDStruct *PID);

#endif



