#include "gpio.h"

BuzzerStruct buzzerStr;

KeyStruct key1Str = {true, true};
KeyStruct key2Str = {true, true};
KeyStruct key3Str = {true, true};
KeyStruct key4Str = {true, true};

void buzzer_entry(void *parameter)
{
    while (1)
    {
        // 接收邮箱数据，如果没有数据则持续等待并释放CPU控制权
        rt_mb_recv(buzzerStr.mailbox, &buzzerStr.mb_data, RT_WAITING_FOREVER);
        BUZZER_ON;
        rt_thread_mdelay(buzzerStr.mb_data); // 延时
        BUZZER_OFF;
    }
}

void key_entry(void *parameter)
{

    // 保存按键状态
    key1Str.last_status = key1Str.status;
    key2Str.last_status = key2Str.status;
    key3Str.last_status = key3Str.status;
    key4Str.last_status = key4Str.status;

    // 读取当前按键状态
    key1Str.status = KEY_GET(KEY_1);
    key2Str.status = KEY_GET(KEY_2);
    key3Str.status = KEY_GET(KEY_3);
    key4Str.status = KEY_GET(KEY_4);

    if (key1Str.status && !key1Str.last_status)
    {
        rt_sem_release(key1Str.sem);
        rt_mb_send(buzzerStr.mailbox, 100); // 给buzzer_mailbox发送100
				
    }
    if (key2Str.status && !key2Str.last_status)
    {
        rt_sem_release(key2Str.sem);
        rt_mb_send(buzzerStr.mailbox, 100); // 给buzzer_mailbox发送100
//				pidStr.Ki += 0.5;
//				rt_kprintf("ki = %d\n", (int)(pidStr.Ki*10));
    }
    if (key3Str.status && !key3Str.last_status)
    {
        rt_sem_release(key3Str.sem);
        rt_mb_send(buzzerStr.mailbox, 100); // 给buzzer_mailbox发送100
//				pidStr.Kp += 5;
//				rt_kprintf("kp = %d\n", (int)(pidStr.Kp*10));
    }
    if (key4Str.status && !key4Str.last_status)
    {
        rt_sem_release(key4Str.sem);
        rt_mb_send(buzzerStr.mailbox, 100); // 给buzzer_mailbox发送100
    }
}

void GPIO_Init(void)
{
    gpio_init(LED_PIN, GPO, 1, GPIO_PIN_CONFIG);
    gpio_init(BUZZER_PIN, GPO, 0, GPIO_PIN_CONFIG);
    gpio_init(KEY_1, GPI, GPIO_HIGH, GPIO_PIN_CONFIG);
    gpio_init(KEY_2, GPI, GPIO_HIGH, GPIO_PIN_CONFIG);
    gpio_init(KEY_3, GPI, GPIO_HIGH, GPIO_PIN_CONFIG);
    gpio_init(KEY_4, GPI, GPIO_HIGH, GPIO_PIN_CONFIG);
}

// 按键初始化
void Key_init(void)
{
    rt_timer_t Timer2;

    Timer2 = rt_timer_create("key", key_entry, RT_NULL, 20, RT_TIMER_FLAG_PERIODIC);

    key1Str.sem = rt_sem_create("key1", 0, RT_IPC_FLAG_FIFO); // 创建按键的信号量，当按键按下就释放信号量，在需要使用按键的地方获取信号量即可
    key2Str.sem = rt_sem_create("key2", 0, RT_IPC_FLAG_FIFO);
    key3Str.sem = rt_sem_create("key3", 0, RT_IPC_FLAG_FIFO);
    key4Str.sem = rt_sem_create("key4", 0, RT_IPC_FLAG_FIFO);

    if (RT_NULL != Timer2)
    {
        rt_timer_start(Timer2);
    }
}

void Buzzer_Init(void)
{

    buzzerStr.mailbox = rt_mb_create("buzzer", 5, RT_IPC_FLAG_FIFO);
    buzzerStr.thread = rt_thread_create("buzzer", buzzer_entry, RT_NULL, 1024, 26, 2);

    // 启动线程
    if (RT_NULL != buzzerStr.thread)
    {
        rt_thread_startup(buzzerStr.thread);
    }
}