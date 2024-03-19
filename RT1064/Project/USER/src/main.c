#include "headfile.h"

void main()
{


	GPIO_Init();		  // 蜂鸣器,LED,按键初始化
	ICAR_Init();
	SERVO_Init();		  // 舵机初始化
	
	MOTOR_Init();
	PID_Init();			  // PID初始化
	Encoder_Init();		  // 编码器初始化
	Timer_PIT_Init();	  // 主控制线程初始化
	Key_init();			  // 按键线程初始化
	Buzzer_Init();		  // 蜂鸣器线程初始化
	Debug_Init();


	USB_Edgeboard_Init(); // USB串口通信初始化
	



	while (1)
	{
		gpio_toggle(LED_PIN);
		//USB_Edgeboard_CarSpeed();
		rt_thread_mdelay(500);
	}
}
