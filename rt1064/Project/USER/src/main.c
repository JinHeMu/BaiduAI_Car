#include "headfile.h"

void main()
{
	

	rt_thread_mdelay(100);					// 延时150ms，等待主板其他外设上电成功
	gpio_init(B9, GPO, 1, GPIO_PIN_CONFIG); // 初始化B9灯


	while (1)
	{
		gpio_toggle(B9);
		rt_thread_mdelay(500);
	}
}
