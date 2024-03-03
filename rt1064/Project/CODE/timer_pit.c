#include "timer_pit.h"

void timer1_pit_entry(void *parameter)//一个时钟节拍一毫秒
{
    static uint32 time;
    time++;
    
    
    if(0 == (time%100))//每0.1s采集一次
    {

    }
		
		if(0 == (time%20))//每0.02s采集一次
    {
		
				
    }
		
		
		

    if(0 == (time%5))//0.005s采集一次
    {
			
    }
		
}


void timer_pit_init(void)
{
    rt_timer_t timer;
    
    //创建一个定时器 周期运行
    timer = rt_timer_create("timer1", timer1_pit_entry, RT_NULL, 1, RT_TIMER_FLAG_PERIODIC);
    
    //启动定时器
    if(RT_NULL != timer)
    {
        rt_timer_start(timer);
    }


    
}