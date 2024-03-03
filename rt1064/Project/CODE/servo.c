#include "servo.h"


// Sample usage:pwm_init(PWM1_MODULE0_CHB_D13, 50, 5000);   
// 初始化PWM1  子模块0 通道B 使用引脚D13  输出PWM频率50HZ   占空比为百分之 5000/PWM_DUTY_MAX*100						PWM_DUTY_MAX在fsl_pwm.h文件中 默认为50000 
// ------------------ 舵机占空比计算方式 ------------------
// 
// 舵机对应的 0-180 活动角度对应 控制脉冲的 0.5ms-2.5ms 高电平
// 
// 那么不同频率下的占空比计算方式就是
// PWM_DUTY_MAX/(1000/freq)*(1+Angle/180) 在 50hz 时就是 PWM_DUTY_MAX/(1000/50)*(1+Angle/180)
// 
// 那么 100hz 下 90度的打角 即高电平时间1.5ms 计算套用为
// PWM_DUTY_MAX/(1000/100)*(1+90/180) = PWM_DUTY_MAX/10*1.5
// 
// ------------------ 舵机占空比计算方式 ------------------

#define SERVO_MOTOR_FREQ 50
#define SERVO_MOTOR_DUTY(x)         ((float)PWM_DUTY_MAX/(1000.0/(float)SERVO_MOTOR_FREQ)*(0.5+(float)(x)/90.0))
#define SERVO_PIN PWM4_MODULE2_CHA_C30
#define SERVO_CENTER 90

void servo_init(void)
{
	pwm_init(SERVO_PIN, 50, SERVO_MOTOR_DUTY(SERVO_CENTER));
}
