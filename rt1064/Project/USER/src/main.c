#include "headfile.h"

void main()
{
	

	rt_thread_mdelay(100);					// ��ʱ150ms���ȴ��������������ϵ�ɹ�
	gpio_init(B9, GPO, 1, GPIO_PIN_CONFIG); // ��ʼ��B9��


	while (1)
	{
		gpio_toggle(B9);
		rt_thread_mdelay(500);
	}
}
