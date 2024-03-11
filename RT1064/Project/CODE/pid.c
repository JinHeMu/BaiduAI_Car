#include "pid.h"


float Incremental_KP = 0;
float Incremental_KI = 0;

// typedef struct 
// {
// 	float Speed_Input;        	            //速度PID，速度设定值
// 	float Speed_FeedBack;                  //速度PID，速度反馈值
//     float Speed_Now_Error;	 	            //速度PID，速度误差,vi_Ref - vi_FeedBack
// 	float Speed_Pre_Error; 	            //速度PID，前一次，速度误差之差，d_error-PreDerror;
// 	float Kp;	 		 			    //比例系数，Kp = Kp
// 	float Ki;		 				    //积分系数，Ki = Kp * ( T / Ti )
// 	float Kd;		 				    //微分系数，Kd = KP * Td * T
// 	float Speed_Output; 				        //PID输出值
// }PIDStruct;

PIDStruct pidStr;

int Incremental_pid(int Target, int Encoder)
{
    static float Bias, Pwm, Last_Bias;
    Bias = (float)(Target - Encoder);
    Pwm += Incremental_KP * (Bias - Last_Bias) + Incremental_KI * Bias;
    Last_Bias = Bias;
    return (int)Pwm;
}


// /**
// * @brief        PID参数初始化
// * @param             
// **/
// void PID_Init(void)          
// {	
//   pidStr.Kp = PID_KP;
//   pidStr.Kd = PID_KD;
//   pidStr.Ki = PID_KI;

//   pidStr.Speed_Input = 0;        	            //速度PID，速度设定值
//   pidStr.Speed_FeedBack = 0;                  //速度PID，速度反馈值
//   pidStr.Speed_Now_Error = 0;	 	            //速度PID，速度误差,vi_Ref - vi_FeedBack
//   pidStr.Speed_Pre_Error = 0; 	            //速度PID，前一次，速度误差之差，d_error-PreDerror;
//   pidStr.Speed_Output = 0;
// }


// /**
// * @brief        PID速控模型
// * @param             
// **/
// signed int PID_MoveCalculate(PIDStruct *pp)                        
// {    
//     float  error,d_error,dd_error; 
			 
//     error = pp->vi_Ref - pp->vi_FeedBack;
//     d_error = error - pp->vi_PreError;
//     dd_error = d_error - pp->vi_PreDerror;          
        
//     pp->vi_PreError = error;		                     
//     pp->vi_PreDerror = d_error;
	
//     if( ( error < VV_DEADLINE ) && ( error > -VV_DEADLINE ) )
//     {
//         ;             
//     }
//     else								
//     { 
// //PID积分包和，必要时候启用，消抖
// //				I_error = pp -> v_Ki * error;
// //				if(I_error >= (VV_MAX/5))
// //				{
// //				I_error = VV_MAX/5;
// //				}
// //				else if(I_error <= (VV_MIN/5))
// //				{
// //				I_error = VV_MIN/5;
// //				}
// //        pp->vl_PreU += (pp -> v_Kp * d_error + I_error + pp->v_Kd*dd_error)/3;
// 				  pp->vl_PreU += (pp -> v_Kp * d_error + pp -> v_Ki * error + pp->v_Kd*dd_error);
//     } 
// 		pp->vl_PreU = pp->vl_PreU;
//     if( pp->vl_PreU >= MOTOR_PWM_MAX )
//     {
//         pp->vl_PreU = MOTOR_PWM_MAX;
//     }
//     else if( pp->vl_PreU <= MOTOR_PWM_MIN )	
//     {
//         pp->vl_PreU = MOTOR_PWM_MIN;
//     }
                                             
//     return (pp->vl_PreU);
// } 



// int IncPID_Calculate(PIDStruct *PID)
// {
//   float  error,last_error,last_last_error; 

//   error =             PID->Speed_Input -  PID->Speed_FeedBack;
//   last_error =        error            -  PID->Speed_Now_Error;
//   last_last_error =   last_error       -  PID->Speed_Pre_Error; 

//   PID->Speed_Now_Error = error;		                     
//   PID->Speed_Pre_Error = last_error;


//     static float Bias4, Pwm4, Last_Bias4;
//     Bias4 = (float)(Target - Encoder);
//     Pwm4 += Incremental_kp[3] * (Bias4 - Last_Bias4) + Incremental_ki[3] * Bias4;
//     Last_Bias4 = Bias4;
//     return (int)Pwm4;
// }

