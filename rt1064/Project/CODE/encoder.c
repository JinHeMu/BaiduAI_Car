#include "encoder.h"

//---------------------�ṹ��---------------------//
struct RC_Para Encoder_Para = {0, 0, 0.25}; // ��ͨ�˲�


RC_Filter_pt RC_Encoder = &Encoder_Para;


int16 encoder=0;
int16 RC_encoder=0;

void encoder_init(void)
{
  // ��ʼ�� QTIMER_1 A��ʹ��QTIMER1_TIMER2_C2 B��ʹ��QTIMER1_TIMER3_C24
  qtimer_quad_init(QTIMER_1, QTIMER1_TIMER0_C0, QTIMER1_TIMER1_C1);
}




void encoder_get(void)
{

  encoder = qtimer_quad_get(QTIMER_1, QTIMER1_TIMER0_C0); // ������Ҫע��ڶ������������дA������

  RC_encoder = (int16_t)RCFilter(encoder, RC_Encoder); // ��ͨ�˲�

  qtimer_quad_clear(QTIMER_1, QTIMER1_TIMER0_C0);
}