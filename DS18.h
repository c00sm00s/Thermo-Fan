#ifndef __DS18_H__
#define __DS18_H__
#include "reg52.h"
#include "main.h"


extern u8 ds_nmb;


//检查DS18B20
void sendChangeCmd();
//获取温度
u16 getTmpValue();




#endif

