#ifndef __GPIO_H__
#define __GPIO_H__

#include "headfile.h"

#define BUZZER_PIN	    B11			// 定义主板上蜂鸣器对应引脚
#define LED_PIN			B9			// 定义主板上LED对应引脚
#define KEY_1 C4    
#define KEY_2 C26   
#define KEY_3 C27   
#define KEY_4 C31 


#define LED_ON          (gpio_set(LED_PIN, 1)) 		
#define LED_OFF         (gpio_set(LED_PIN, 0)) 									

#define BUZZER_ON        (gpio_set(BUZZER_PIN, 1))  			
#define BUZZER_OFF       (gpio_set(BUZZER_PIN, 0))
#define BuzzerOk			70
#define BuzzerWarnning		100
#define BuzzerDing			30
#define BuzzerSysStart		60
#define BuzzerFinish		200

#define KEY_GET(x)		(gpio_get(x))


typedef struct 
{
	bool status;
	bool last_status;
	rt_sem_t sem;

}KeyStruct;

typedef struct 
{

    rt_thread_t thread;
	rt_ubase_t mb_data;
	rt_mailbox_t mailbox;

}BuzzerStruct;


extern BuzzerStruct buzzerStr;


void GPIO_Init(void);
void Key_init(void);
void Buzzer_Init(void);


#endif