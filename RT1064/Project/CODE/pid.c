#include "pid.h"

PIDStruct pidStr;

/**
* @brief        PID参数初始化
* @param             
**/
void PID_Init(void)          
{	
  pidStr.Kp = PID_KP;
  pidStr.Kd = PID_KD;
  pidStr.Ki = PID_KI;

  pidStr.Speed_Target    = 0;        	            //速度PID，速度设定值
  pidStr.Speed_FeedBack  = 0;                  //速度PID，速度反馈值
  pidStr.Speed_Output    = 0;
  pidStr.Speed_Now_Error = 0;	 	            //速度PID，速度误差,vi_Ref - vi_FeedBack
	pidStr.Speed_Pre_Error = 0; 	            //速度PID，前一次，速度误差之差，d_error-PreDerror;
}


/**
* @brief        PID计算
* @param        PIDStruct结构体指针
* @return       PID输出      
**/
signed int PID_MoveCalculate(PIDStruct *PID)
{
    PID->Speed_Now_Error = PID->Speed_Target - PID->Speed_FeedBack;
    PID->Speed_Output   += PID->Kp * (PID->Speed_Now_Error - PID->Speed_Pre_Error) + PID->Ki * PID->Speed_Now_Error;//增量式PI控制器
    PID->Speed_Pre_Error = PID->Speed_Now_Error;
    return (int)PID->Speed_Output;
}


int Incremental_pid1(int Target, int Encoder)
{
    static float Bias1, Pwm1, Last_Bias1;
    Bias1 = (float)(Target - Encoder);
    Pwm1 += pidStr.Kp * (Bias1 - Last_Bias1)  + pidStr.Ki * Bias1;
    Last_Bias1 = Bias1;
    return (int)Pwm1;
}










static void pid_test(int argc, char**argv)
{
	float time = strtof(argv[1], NULL); // 将字符串转换为浮点数
	icarStr.SpeedTarget = 0.3;
	rt_thread_mdelay(time);
	icarStr.SpeedTarget = 0.0;
	icarStr.SpeedTarget = -0.3;
	rt_thread_mdelay(time);
	icarStr.SpeedTarget = 0.0;

}
MSH_CMD_EXPORT(pid_test, time);




