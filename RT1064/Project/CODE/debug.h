#ifndef __DEBUG_H__
#define __DEBUG_H__

#include "headfile.h"


typedef struct 
{

	rt_thread_t thread;

}DebugStruct;

extern bool flag;

void Debug_Init(void);



#endif