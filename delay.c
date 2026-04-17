#include "reg52.h"
#include "delay.h"
#include "main.h"
#include "intrins.h"


//100us级软件延迟
void delay(uint x)
{
	uint a,b;
	for(a=x;a>0;a--)
		for(b=10;b>0;b--); 
}


//微秒级延迟 不是很准 使用时要校准
void delay_us( u16 i )
{
	while(i--);
}

void Delay1000us()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
}



//1ms级软件延迟
void delay1(uint x)
{
	uint a,b;
	for(a=x;a>0;a--)
		for(b=114;b>0;b--); 
}


void delay_ms( u32 i )
{
	u32 ii=0;
	for( ii=0; ii<i; ii++ )
	{
		Delay1000us();
	}
}




