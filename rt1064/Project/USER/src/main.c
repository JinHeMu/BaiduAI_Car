#include "headfile.h"

void main()
{
	

	rt_thread_mdelay(150);					// 延时150ms，等待主板其他外设上电成功
	gpio_init(B9, GPO, 1, GPIO_PIN_CONFIG); // 初始化B9灯

	servo_init();

	display_init(); // 显示屏初始化	
	
	buzzer_init(); // 初始化蜂鸣器
	button_init(); // 初始化按键

	encoder_init();	  // 初始化编码器

	timer_pit_init(); // 周期定时器
	
	while (1)
	{
		gpio_toggle(B9);
		rt_thread_mdelay(500);
	}
}
