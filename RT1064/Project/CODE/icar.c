#include "icar.h"

IcarStruct icarStr;




void ICAR_Init(void)
{
	icarStr.SpeedTarget = 0.0f;				    //电机目标速度：m/s	
	icarStr.SpeedFeedback = 0.0f;		        //电机模型实测速度：m/s
	icarStr.SpeedMaxRecords = 0.0f;
 	icarStr.ServoPwmSet = servoStr.thresholdMiddle;
}