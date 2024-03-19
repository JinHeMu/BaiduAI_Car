#include "timer_pit.h"

void Timer_PIT_entry(void *parameter)//一个时钟节拍10毫秒
{

    Encoder_Get();
    MOTOR_ControlLoop(icarStr.SpeedTarget);//电机闭环控制
	if(flag)
	{
		rt_kprintf("targer:%d,%d\n", (int)pidStr.Speed_Target, (int)pidStr.Speed_FeedBack);
		
	}

//		MOTOR_ControlLoop(0.3);//电机闭环控制
	
}


void Timer_PIT_Init(void)
{
    rt_timer_t Timer1;
    
    //创建一个定时器 周期运行
    Timer1 = rt_timer_create("Timer1", Timer_PIT_entry, RT_NULL, 10, RT_TIMER_FLAG_PERIODIC);
    
    //启动定时器
    if(RT_NULL != Timer1)
    {
        rt_timer_start(Timer1);
    }
    
}