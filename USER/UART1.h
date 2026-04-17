#ifndef __UART_H__
#define __UART_H__
#include "main.h"
#include "reg52.h"

extern bit busy;

//串口初始化	
void UartInit();

//发送一个字节
void U1_TX(char DATA);

//发送多个字节
void U1_TXDATA(u16 nmb, char * DATA );





#endif


