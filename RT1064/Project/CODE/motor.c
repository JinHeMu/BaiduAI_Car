#include "motor.h"

MotorStruct motorStr;

/**
* @brief        电机输出PWM设置
* @param        pwm：-4000~4000
* @ref          
* @author       Leo
* @note         
**/
void MOTOR_SetPwmValue(signed int pwm)
{   
    
    if (pwm >= 0)
    {
        if(pwm > MOTOR_PWM_MAX) pwm = MOTOR_PWM_MAX;
        gpio_set(MOTOR_DIR, 0);
        pwm_duty(MOTOR_PWM, pwm);
    }
    else
    {   
        if(pwm < MOTOR_PWM_MIN) pwm = MOTOR_PWM_MIN;
        gpio_set(MOTOR_DIR, 1);
        pwm_duty(MOTOR_PWM, -pwm);
    }
}


/**
* @brief        电机闭环速控
* @param        speed：速度m/s     
**/
void MOTOR_ControlLoop(float speed)
{	
    if(speed > MOTOR_SPEED_MAX)
        speed = MOTOR_SPEED_MAX;
    else if(speed < -MOTOR_SPEED_MAX)
        speed = -MOTOR_SPEED_MAX;

    //pidStr.Speed_Target为编码器的值(10ms控制周期)
    pidStr.Speed_Target = (float)(speed*MOTOR_CONTROL_CYCLE / motorStr.DiameterWheel / PI * motorStr.EncoderLine * 4.0f * motorStr.ReductionRatio);
    
    MOTOR_SetPwmValue(PID_MoveCalculate(&pidStr));
}

void MOTOR_Init(void)
{
    gpio_init(MOTOR_DIR, GPO, 0, GPIO_PIN_CONFIG); // 单片机端口D2 初始化DIR_1			GPIO
    pwm_init(MOTOR_PWM, MOTOR_FREQ, 0);            // 单片机端口D0 初始化PWM_1周期12K 占空比0 

    motorStr.EncoderLine = 512.0f; 							//编码器线数=光栅数16*4				
    motorStr.ReductionRatio = 2.7f;							//电机减速比								
    motorStr.EncoderValue = 0;
    motorStr.DiameterWheel = 0.064f;//68cm					//轮子直径:m
    motorStr.CloseLoop = true;                              //默认闭环模式
}

static void motor_test(int argc, char**argv)
{

	signed int pwm = atoi(argv[1]); // 将字符串转换为浮点数
    MOTOR_SetPwmValue(pwm);

}

MSH_CMD_EXPORT(motor_test, pwm);
