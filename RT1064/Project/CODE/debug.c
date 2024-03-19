#include "debug.h"


DebugStruct debugSrc;
bool flag = false;

void debug_entry(void *parameter)
{
	rt_ubase_t mb_data;
	while(1)
	{
        // 接收邮箱数据，如果没有数据则持续等待并释放CPU控制权
      rt_mb_recv(keymailbox, &mb_data, RT_WAITING_FOREVER);
		switch (mb_data)
		{
		case 1:
			rt_kprintf("1\n");
			USB_Edgeboard_TransmitKey(100);
			break;
		case 2:
			rt_kprintf("2\n");
			break;
		case 3:
			rt_kprintf("3\n");
			break;
		case 4:
			rt_kprintf("4\n");
			break;
		default:
			break;
		}
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
