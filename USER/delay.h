#ifndef __DELAY_H__
#define __DELAY_H__
#include "main.h"
#include "reg52.h"

//100us级软件延迟
void delay(uint x);
//1ms级软件延迟
void delay1(uint x);

void delay_ms( u32 i );

void Delay1000us();		//@11.0592MHz

void delay_us( u16 i );
#endif
