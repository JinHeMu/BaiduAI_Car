/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,闁跨喐鏋婚幏椋庡悢閽€宥夋晸閿燂拷
 * All rights reserved.
 * 闁跨喐鏋婚幏鐑芥晸閺傘倖瀚归柨鐔告灮閹风兘鏁撻弬銈嗗QQ缂囥倝鏁撻弬銈嗗娑撯偓缂囥倝鏁撻弬銈嗗179029047(闁跨喐鏋婚幏鐑芥晸閺傘倖瀚�)  闁跨喐鏋婚幏椋庡參闁跨喐鏋婚幏锟�244861897
 *
 * 闁跨喐鏋婚幏鐑芥晸閺傘倖瀚归柨鐔告灮閹风兘鏁撻弬銈嗗闁跨喐鏋婚幏鐑芥晸閹瑰嘲搴滈幏閿嬫綀闁跨喐鏋婚幏鐑芥晸閺傘倖瀚归柨鐔告灮閹烽鍚旈拃宥夋晸閺傘倖瀚归柨鐔告灮閹烽攱鐗庨柨鐔诲▏鏉堢偓瀚归柨鐔告灮閹风兘鏁撻弬銈嗗闁跨喐鏋婚幏鐑芥晸閺傘倖瀚归柨鐔告灮閹风兘鏁撻弬銈嗗闁跨喐鏋婚幏鐑芥晸閹活厾顣幏鐑芥晸闁板灚鎷濋幏鐑芥晸閿燂拷
 * 闁跨喐鏋婚幏鐤箣闁跨喐鏋婚幏铚傜秴娴ｅ潡鏁撻惌顐ヮ嚋閹风兘鏁撻弬銈嗗闁跨喐鏋婚幏鐑芥晸閺傘倖瀚归柨鐔告灮閹风兘鏁撻弬銈嗗闁跨喓娼鹃棃鈺傚闁跨喐鏋婚幏鐑芥晸閺傘倖瀚归弮鍫曟晸閺傘倖瀚归柨鐔活嚑娣囨繈鏁撻弬銈嗗闁跨喐鏋婚幏椋庡悢閽€宥夋晸閺傘倖瀚归梽宀勬晸妤椾警鐓夐幏鐑芥晸閺傘倖瀚归柨鐔告灮閹风兘鏁撻敓锟�
 *
 * @file       		headfile
 * @company	   		闁跨喓鍗崇拋瑙勫闁跨喐鏋婚幏椋庡悢閽€宥夋晸閺傘倖瀚归柨鐔告灮閹风柉鏌婇柨鐔峰閿燂拷
 * @author     		闁跨喐鏋婚幏椋庡悢閽€宥夋晸閿燂拷(QQ3184284598)
 * @version    		闁跨喍绮欓惇濯巓c闁跨喐鏋婚幏绌爀rsion闁跨喍鑼庣涵閿嬪 闁跨喕濮ら張顒冾嚛闁跨喐鏋婚幏锟�
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

//------闁跨喍鑼庣涵閿嬪缁崵绮洪柨鐔告灮閹风兘鏁撻柊闈涘殩閹峰嘲瀚欓柨鐕傛嫹
#include "ff.h"
#include "diskio.h"
#include "fsl_sd_disk.h"

#include "SEEKFREE_PRINTF.h"


//------闁跨喐鏋婚幏椋庡悢閽€宥夋晸閺傘倖瀚归柨鐔哄珱椤掑﹥瀚归柨鐔告灮閹风兘鏁撻弬銈嗗闁跨喐鏋婚幏鐑芥晸閺傘倖瀚归柨鐔煎徍閸戙倖瀚归崟鐔兼晸閿燂拷
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

//------闁跨喐鏋婚幏椋庡悢閽€宥夋晸閺傘倖瀚归柨鐔哄珱閸戙倖瀚归柨鐔告灮閹风兘鏁撻柊闈涘殩閹峰嘲瀚欓柨鐕傛嫹
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
#include "motor.h"
#include "encoder.h"
#include "timer_pit.h"
#include "display.h"
#include "servo.h"
#include "buzzer.h"
#include "button.h"
#include "filter.h"

#endif

