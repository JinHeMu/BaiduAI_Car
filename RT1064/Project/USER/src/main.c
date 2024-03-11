#include "headfile.h"

void main()
{
	

	rt_thread_mdelay(100);					
	gpio_init(B9, GPO, 1, GPIO_PIN_CONFIG);


	while (1)
	{
		gpio_toggle(B9);
		rt_thread_mdelay(500);
	}

}
