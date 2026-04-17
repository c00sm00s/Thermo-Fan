#ifndef __PID_H__
#define __PID_H__
#include "main.h"
#include "reg52.h"

sbit IO1=P1^0;
sbit IO2=P1^1;

extern u8 PID0_H;
extern u8 PID1_H;

void TIME_Init();



#endif
