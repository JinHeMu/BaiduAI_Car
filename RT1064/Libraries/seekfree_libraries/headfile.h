/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,闂佽法鍠愰弸濠氬箯妞嬪骸鎮㈤柦鈧澶嬫櫢闁跨噦鎷�
 * All rights reserved.
 * 闂佽法鍠愰弸濠氬箯閻戣姤鏅搁柡鍌樺€栫€氬綊鏌ㄩ悢鍛婄伄闁归鍏橀弫鎾诲棘閵堝棗顏禥Q缂傚洢鍊濋弫鎾诲棘閵堝棗顏跺☉鎾亾缂傚洢鍊濋弫鎾诲棘閵堝棗顏�179029047(闂佽法鍠愰弸濠氬箯閻戣姤鏅搁柡鍌樺€栫€氾拷)  闂佽法鍠愰弸濠氬箯妞嬪骸鍙冮梺璺ㄥ枑閺嬪骞忛敓锟�244861897
 *
 * 闂佽法鍠愰弸濠氬箯閻戣姤鏅搁柡鍌樺€栫€氬綊鏌ㄩ悢鍛婄伄闁归鍏橀弫鎾诲棘閵堝棗顏堕梺璺ㄥ枑閺嬪骞忛悜鑺ユ櫢闁圭懓鍢叉惔婊堝箯闁垮缍€闂佽法鍠愰弸濠氬箯閻戣姤鏅搁柡鍌樺€栫€氬綊鏌ㄩ悢鍛婄伄闁圭兘顥撻崥鏃堟媰瀹ュ鏅搁柡鍌樺€栫€氬綊鏌ㄩ悢鍛婄伄闁圭兘鏀遍悧搴ㄦ煥閻旇鈻忛弶鍫㈠亾鐎氬綊鏌ㄩ悢鍛婄伄闁归鍏橀弫鎾诲棘閵堝棗顏堕梺璺ㄥ枑閺嬪骞忛悜鑺ユ櫢闁哄倶鍊栫€氬綊鏌ㄩ悢鍛婄伄闁归鍏橀弫鎾诲棘閵堝棗顏堕梺璺ㄥ枑閺嬪骞忛悜鑺ユ櫢闁规椿鍘鹃。顕€骞忛悜鑺ユ櫢闂佹澘鐏氶幏婵嬪箯閻戣姤鏅搁柨鐕傛嫹
 * 闂佽法鍠愰弸濠氬箯閻ゎ垳绠ｉ梺璺ㄥ枑閺嬪骞忛摎鍌滅Т濞达絽娼￠弫鎾绘儗椤愩儺鍤嬮柟椋庡厴閺佹捇寮妶鍡楊伓闂佽法鍠愰弸濠氬箯閻戣姤鏅搁柡鍌樺€栫€氬綊鏌ㄩ悢鍛婄伄闁归鍏橀弫鎾诲棘閵堝棗顏堕梺璺ㄥ枔濞奸箖妫冮埡鍌氼伓闂佽法鍠愰弸濠氬箯閻戣姤鏅搁柡鍌樺€栫€氬綊寮崼鏇熸櫢闁哄倶鍊栫€氬綊鏌ㄩ悢娲诲殤濞ｅ洦绻堥弫鎾诲棘閵堝棗顏堕梺璺ㄥ枑閺嬪骞忔搴℃偄闁解偓瀹ュ鏅搁柡鍌樺€栫€氬綊姊藉畝鍕櫢濡ゆぞ璀﹂悡澶愬箯閻戣姤鏅搁柡鍌樺€栫€氬綊鏌ㄩ悢鍛婄伄闁归鍏橀弫鎾绘晸閿燂拷
 *
 * @file       		headfile
 * @company	   		闂佽法鍠撻崡宕囨媼鐟欏嫬顏堕梺璺ㄥ枑閺嬪骞忔搴℃偄闁解偓瀹ュ鏅搁柡鍌樺€栫€氬綊鏌ㄩ悢鍛婄伄闁归鏌夐弻濠囨煥閻斿嘲顥為柨鐕傛嫹
 * @author     		闂佽法鍠愰弸濠氬箯妞嬪骸鎮㈤柦鈧澶嬫櫢闁跨噦鎷�(QQ3184284598)
 * @version    		闂佽法鍠嶇划娆撴儑婵窊c闂佽法鍠愰弸濠氬箯缁岀垁rsion闂佽法鍠嶉懠搴ｆ兜闁垮顏� 闂佽法鍠曟慨銈夊嫉椤掑喚鍤涢梺璺ㄥ枑閺嬪骞忛敓锟�
 * @Software 		IAR 8.3 or MDK 5.28
 * @Target core		NXP RT1064DVL6A
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-04-30
 ********************************************************************************************************************/
 
#ifndef _headfile_h
#define _headfile_h


#include <stdint.h>
#include "fsl_common.h"

#include "fsl_debug_console.h"
#include "fsl_iomuxc.h"
#include "fsl_pit.h"

#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_cache.h"
#include "common.h"
#include "zf_vector.h"

//------闂佽法鍠嶉懠搴ｆ兜闁垮顏剁紒顖濆吹缁椽鏌ㄩ悢鍛婄伄闁归鍏橀弫鎾绘煀闂堟稑娈╅柟宄板槻鐎氭瑩鏌ㄩ悤鍌涘
#include "ff.h"
#include "diskio.h"
#include "fsl_sd_disk.h"

#include "SEEKFREE_PRINTF.h"


//------闂佽法鍠愰弸濠氬箯妞嬪骸鎮㈤柦鈧澶嬫櫢闁哄倶鍊栫€氬綊鏌ㄩ悢鍝勭彵妞ゆ帒锕ョ€氬綊鏌ㄩ悢鍛婄伄闁归鍏橀弫鎾诲棘閵堝棗顏堕梺璺ㄥ枑閺嬪骞忛悜鑺ユ櫢闁哄倶鍊栫€氬綊鏌ㄩ悢鐓庡緧闁告垯鍊栫€氬綊宕熼悢鍏兼櫢闁跨噦鎷�
#include "zf_gpio.h"
#include "zf_iomuxc.h"
#include "zf_pit.h"
#include "zf_pwm.h"
#include "zf_uart.h"
#include "zf_spi.h"
#include "zf_systick.h"
#include "zf_qtimer.h"
#include "zf_adc.h"
#include "zf_iic.h"
#include "zf_flash.h"
#include "zf_camera.h"
#include "zf_csi.h"
#include "zf_rom_api.h"
#include "zf_usb_cdc.h"
#include "zf_sdcard.h"

//------闂佽法鍠愰弸濠氬箯妞嬪骸鎮㈤柦鈧澶嬫櫢闁哄倶鍊栫€氬綊鏌ㄩ悢鍝勭彵闁告垯鍊栫€氬綊鏌ㄩ悢鍛婄伄闁归鍏橀弫鎾绘煀闂堟稑娈╅柟宄板槻鐎氭瑩鏌ㄩ悤鍌涘
#include "SEEKFREE_FONT.h"
#include "SEEKFREE_18TFT.h"
#include "SEEKFREE_IPS114_SPI.h"
#include "SEEKFREE_IPS200.h"
#include "SEEKFREE_IIC.h"
#include "SEEKFREE_VIRSCO.h"
#include "SEEKFREE_FUN.h"
#include "SEEKFREE_MPU6050.h"
#include "SEEKFREE_OLED.h"
#include "SEEKFREE_NRF24L01.h"
#include "SEEKFREE_MMA8451.h"
#include "SEEKFREE_L3G4200D.h"
#include "SEEKFREE_ICM20602.h"
#include "SEEKFREE_MT9V03X.h"
#include "SEEKFREE_WIRELESS.h"
#include "SEEKFREE_MT9V03X_CSI.h"
#include "SEEKFREE_W25QXXJV.h"
#include "SEEKFREE_SCC8660_CSI.h"
#include "SEEKFREE_SCC8660.h"
#include "SEEKFREE_BLUETOOTH_CH9141.h"
#include "SEEKFREE_GPS_TAU1201.h"
#include "SEEKFREE_IMU963RA.h"

////------User Defined
#include "rtthread.h"
#include "uart1_usb.h"
#include "servo.h"
#include "encoder.h"
#include "common.h"
#include "pid.h"
#include "motor.h"


typedef union 
{
	uint8_t U8_Buff[2];
	uint16_t U16;
	int16_t S16;
}Bint16_Union;
	
typedef union 
{
	uint8_t U8_Buff[4];
	float Float;
    unsigned long U32;
}Bint32_Union;


#endif

