#include "motor.h"

MotorStruct motorStr;

void MOTOR_Init(void)
{
    gpio_init(MOTOR_DIR, GPO, 0, GPIO_PIN_CONFIG); // 单片机端口D0 初始化DIR_1			GPIO
    pwm_init(MOTOR_PWM, MOTOR_FREQ, 0);            // 单片机端口D2 初始化PWM_1周期12K 占空比0 

    motorStr.EncoderLine = 512.0f; 							//编码器线数=光栅数16*4				
    motorStr.ReductionRatio = 2.7f;							//电机减速比								
    motorStr.EncoderValue = 0;
    motorStr.DiameterWheel = 0.064f;//68cm					//轮子直径:m
    motorStr.CloseLoop = true;                              //默认闭环模式
}

/**
* @brief        电机输出PWM设置
* @param        pwm：-2000~2000
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

    //pidStr.vi_Ref为编码器的速度
    pidStr.Speed_Input = (float)(speed*MOTOR_CONTROL_CYCLE / motorStr.DiameterWheel / PI * motorStr.EncoderLine * 4.0f * motorStr.ReductionRatio);
    
    MOTOR_SetPwmValue(Incremental_pid(pidStr.Speed_Input, pidStr.Speed_FeedBack));
}


// /**
// * @brief        电机闭环速控
// * @param        speed：速度m/s
// * @ref          
// * @author       Leo
// * @note         
// **/
// void MOTOR_ControlLoop(float speed)
// {	
//     if(speed > MOTOR_SPEED_MAX)
//         speed = MOTOR_SPEED_MAX;
//     else if(speed < -MOTOR_SPEED_MAX)
//         speed = -MOTOR_SPEED_MAX;
    
//     pidStr.vi_Ref = (float)(speed*MOTOR_CONTROL_CYCLE / motorStr.DiameterWheel / PI * motorStr.EncoderLine * 4.0f * motorStr.ReductionRatio);
    
//     MOTOR_SetPwmValue(PID_MoveCalculate(&pidStr));
// }






// /**
// * @brief        电机控制线程
// * @param        
// * @ref          
// * @author       Leo
// * @note         
// **/
// void MOTOR_Timer(void)
// {
//     motorStr.Counter++;
//     if(motorStr.Counter >= 10)							    //速控:10ms
//     {
//         ENCODER_RevSample();								//编码器采样

//         if(icarStr.sprintEnable || usbStr.connected)        //通信连接或电机测试才开启闭环（保护+省电）
//         {
//             if(motorStr.CloseLoop)
//             {
//                 MOTOR_ControlLoop(icarStr.SpeedSet);		//闭环速控
//             }
//             else//开环百分比控制
//             {
//                 if(icarStr.SpeedSet > 100)
//                     icarStr.SpeedSet = 100;
//                 else if(icarStr.SpeedSet < -100)
//                     icarStr.SpeedSet = -100;
//                 signed int speedRate = MOTOR_PWM_MAX/100.f*icarStr.SpeedSet; //开环：百分比%
                
//                 MOTOR_SetPwmValue(speedRate);		//开环速控
//             }
//         }
//         else
//         {
//             MOTOR_SetPwmValue(0);
//         }
       
//         motorStr.Counter = 0;
//     }
// }