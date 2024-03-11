#include "timer_pit.h"

void Timer_PIT_entry(void *parameter)//一个时钟节拍一毫秒
{
    static uint32 time;
    time++;
      	
    if(0 == (time%10))//10ms采集一次
    {
		Encoder_Get();


        //MOTOR_ControlLoop();
        // if(icarStr.sprintEnable || usbStr.connected)        //通信连接或电机测试才开启闭环（保护+省电）
        // {
        //     if(motorStr.CloseLoop)
        //     {
        //         MOTOR_ControlLoop(icarStr.SpeedSet);		//闭环速控
        //     }
        //     else//开环百分比控制
        //     {
        //         if(icarStr.SpeedSet > 100)
        //             icarStr.SpeedSet = 100;
        //         else if(icarStr.SpeedSet < -100)
        //             icarStr.SpeedSet = -100;
        //         signed int speedRate = MOTOR_PWM_MAX/100.f*icarStr.SpeedSet; //开环：百分比%
                
        //         MOTOR_SetPwmValue(speedRate);		//开环速控
        //     }
        // }
        // else
        // {
        //     MOTOR_SetPwmValue(0);
        // }	

    }
		
}


void Timer_PIT_Init(void)
{
    rt_timer_t Timer_Src;
    
    //创建一个定时器 周期运行
    Timer_Src = rt_timer_create("Timer", Timer_PIT_entry, RT_NULL, 1, RT_TIMER_FLAG_PERIODIC);
    
    //启动定时器
    if(RT_NULL != Timer_Src)
    {
        rt_timer_start(Timer_Src);
    }


    
}