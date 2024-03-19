#include "debug.h"


DebugStruct debugSrc;
bool flag = false;

void debug_entry(void *parameter)
{
	while(1)
	{
		rt_sem_take(key4Str.sem, RT_WAITING_FOREVER);
		flag = true;
		icarStr.SpeedTarget = 0.3;
		rt_thread_mdelay(2000);
		icarStr.SpeedTarget = 0.0;
		rt_thread_mdelay(2000);
		icarStr.SpeedTarget = -0.3;
		rt_thread_mdelay(2000);
		icarStr.SpeedTarget = 0.0;
		flag = false;
		
	}
	
	
	
	
	
}


void Debug_Init(void)
{

    
    debugSrc.thread = rt_thread_create("debug", debug_entry, RT_NULL, 1024, 31, 2);

    // 启动线程
    if (RT_NULL != debugSrc.thread)
    {
        rt_thread_startup(debugSrc.thread);
    }
}
