#include "motor.h"

#define PWM_LIMIT 25000// 限幅，必须注意安全

#define DIR D0
#define PWM PWM2_MODULE3_CHA_D2

int32 duty = 0;

float Incremental_kp = 0;
float Incremental_ki = 0;
float Incremental_kd = 0;

void motor_init(void)
{
    gpio_init(DIR, GPO, 0, GPIO_PIN_CONFIG); // 单片机端口D0 初始化DIR_			GPIO
    pwm_init(PWM, 12000, 0);                 // 单片机端口D2 初始化PWM_周期12K 占空比0
}


int Incrementa_pid(int Target, int Encoder)
{
    static float Bias, Pwm, Last_Bias;
    Bias = (float)(Target - Encoder);
    Pwm += Incrementa_kp * (Bias - Last_Bias)  + Incrementa_ki * Bias;
    Last_Bias = Bias;
    return (int)Pwm;
}


void pid_calculate(void)
{
	duty = Incremental_pid(speed_tar, RC_encoder); // 计算得到每个电机输出目标值
	duty = limit(duty, PWM_LIMIT);

}


void motor_control(bool run)
{
    if (run)
    {
        pid_calculate();
    }
    else
    {
        duty = 0;
    }
    if (duty >= 0)
    {
        gpio_set(DIR, 0);
        pwm_duty(PWM, duty);
    }
    else
    {
        gpio_set(DIR, 1);
        pwm_duty(PWM, -duty);
    }
}