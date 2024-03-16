#include "encoder.h"

struct RC_Para Encoder_Para = {0, 0, 0.25}; // 低通滤波

RC_Filter_pt RC_Encoder = &Encoder_Para;

int16_t encoder,RC_encoder;


void Encoder_Get(void)
{

  encoder = qtimer_quad_get(QTIMER_1, QTIMER1_TIMER0_C0); // 这里需要注意第二个参数务必填写A相引脚

  motorStr.EncoderValue = (int16_t)RCFilter(encoder, RC_Encoder); // 低通滤波


  if(motorStr.EncoderValue > 32767)
      motorStr.EncoderValue = motorStr.EncoderValue - 65536;
  
      //PID负反馈数据输入
  pidStr.Speed_FeedBack = motorStr.EncoderValue;
    
  //计算实际速度	---		m/s
  //icarStr.SpeedFeedback = (float)(motorStr.EncoderValue * PI * motorStr.DiameterWheel)/ MOTOR_CONTROL_CYCLE / motorStr.EncoderLine / 4.0f / motorStr.ReductionRatio; //  m/s

  qtimer_quad_clear(QTIMER_1, QTIMER1_TIMER0_C0);

}


void Encoder_Init(void)
{
  // 初始化 QTIMER_1 A相使用QTIMER1_TIMER0_C0 B相使用QTIMER1_TIMER1_C1
  qtimer_quad_init(QTIMER_1, QTIMER1_TIMER0_C0, QTIMER1_TIMER1_C1);

}