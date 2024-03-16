#include "servo.h"

#define SERVO_MOTOR_DUTY(Angle)         ((float)PWM_DUTY_MAX/(1000.0/(float)SERVO_MOTOR_FREQ)*(0.5+(float)(Angle)/90.0))
 
//servoStr.thresholdMiddle在flash里面储存
ServoStruct servoStr = {
	.thresholdMiddle = SERVO_PWM_MIDDLE,  // 舵机中值PWM为 1500
	.thresholdLeft = SERVO_PWM_MAX_L,    // 舵机左向转角最大值PWM为 1150
	.thresholdRight = SERVO_PWM_MAX_R    // 舵机右向转角最大值PWM为 1850
};



/**
* @brief        舵机输出PWM设置
* @param        pwm：-20000~20000       
**/
void SERVO_SetPwmValue(signed int pwm)
{   
    pwm = 3000 - pwm;  //左→右
        
    if(pwm < SERVO_PWM_MIN)
        pwm = SERVO_PWM_MIN;
    else if(pwm > SERVO_PWM_MAX)
        pwm = SERVO_PWM_MAX;
 
    pwm_duty(SERVO_MOTOR_PWM, pwm);
}

/**
* @brief        舵机输出PWM设置（矫正后）
* @param        pwm：500~2500
* @ref          
* @author       Leo
* @note         
**/
uint16_t pwm_Servo = 0;
void SERVO_SetPwmValueCorrect(signed int pwm)
{   
    pwm = 3000 - pwm;  //左→右
    
    pwm -= servoStr.thresholdMiddle-SERVO_PWM_MIDDLE; //中值补偿
	
	uint16_t pwmMax = 3000 - servoStr.thresholdLeft;
	uint16_t pwmMin = 3000 - servoStr.thresholdRight;
	if(pwm < pwmMin)
        pwm = pwmMin;
    else if(pwm > pwmMax)
        pwm = pwmMax;
	
	pwm_Servo = pwm;
    pwm_duty(SERVO_MOTOR_PWM, pwm);
}

/**
* @brief       舵机角度控制 
* @param       angle(>0向右转,<0向左转) 
* @ref                
**/
uint16_t ServoPwm = 1500;
void SERVO_AngleControl(float angle)
{
	uint16_t pwm = 1500;
	angle = -angle;
	if(angle > SERVO_ANGLE_MAX)
		angle = SERVO_ANGLE_MAX;
	else if(angle < -SERVO_ANGLE_MAX)
		angle = -SERVO_ANGLE_MAX;
	
	if(angle >= 0)  //右转
		pwm = (float)angle/SERVO_ANGLE_MAX * (SERVO_PWM_MAX_R-servoStr.thresholdMiddle) + servoStr.thresholdMiddle;		//绝对角度计算
	else if(angle < 0)  	//左转
		pwm = (float)angle/SERVO_ANGLE_MAX * (servoStr.thresholdMiddle - SERVO_PWM_MAX_L) + servoStr.thresholdMiddle;		//绝对角度计算
	
	ServoPwm = pwm;
	SERVO_SetPwmValue(pwm);
}

void SERVO_Init(void)
{
    pwm_init(SERVO_MOTOR_PWM, SERVO_MOTOR_FREQ, SERVO_PWM_MIDDLE);

}


static void servo_test(int argc, char**argv)
{

	float angle = strtof(argv[1], NULL); // 将字符串转换为浮点数
	if (abs(angle) > SERVO_ANGLE_MAX)
	{
		rt_kprintf("angle should be [-%d, %d]\n", SERVO_ANGLE_MAX, SERVO_ANGLE_MAX);
	}
	else
	{
		SERVO_AngleControl(angle);
		rt_kprintf("angle = %f\n", angle);
	}
	

}

MSH_CMD_EXPORT(servo_test, angle);
