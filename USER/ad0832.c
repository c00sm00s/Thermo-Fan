#include "ad0832.h"
#include "reg52.h"
#include "delay.h"
#include "intrins.h"

//sbit ADC0832_CS1	= P1^2;
//sbit ADC0832_DAT1	= P1^6;
//sbit ADC0832_SCL1	= P1^3;


sbit ADC0832_CS	= P1^0;
sbit ADC0832_DAT	= P1^2;
sbit ADC0832_SCL	= P1^1;

////ADC转换
//unsigned char ADC0832_Get1(unsigned char CH)
//{
//	unsigned char i,test,adval;
//	unsigned char dat = 0;	//AD值
//	adval = 0x00;
//	test = 0x00;

//	ADC0832_SCL1 = 0;	//初始化
//	ADC0832_DAT1 = 1;
//	_nop_();
//	ADC0832_CS1 = 0;
//	_nop_();
//	ADC0832_SCL1 = 1;
//	_nop_();
//	if ( CH==0 )	//通道选择
//	{
//		ADC0832_SCL1 = 0;
//		ADC0832_DAT1 = 1;	//通道0的第一位
//		_nop_();
//		ADC0832_SCL1 = 1;
//		_nop_();
//		ADC0832_SCL1 = 0;
//		ADC0832_DAT1 = 0;	//通道0的第二位
//		_nop_();
//		ADC0832_SCL1 = 1;
//		_nop_();
//	}else
//	{
//		ADC0832_SCL1 = 0;
//		ADC0832_DAT1 = 1;	//通道1的第一位
//		_nop_();
//		ADC0832_SCL1 = 1;
//		_nop_();
//		ADC0832_SCL1 = 0;
//		ADC0832_DAT1 = 1;	//通道1的第二位
//		_nop_();
//		ADC0832_SCL1 = 1;
//		_nop_();
//	}

//	ADC0832_SCL1 = 0;
//	ADC0832_DAT1 = 1;
//	for( i = 0;i < 8;i++ )	//读取前8位的值
//	{
//		_nop_();
//		adval <<= 1;
//		ADC0832_SCL1 = 1;
//		_nop_();
//		ADC0832_SCL1 = 0;
//		if (ADC0832_DAT1)adval |= 0x01;
//		else adval |= 0x00;
//	}
//	for (i = 0; i < 8; i++)	//读取后8位的值
//	{
//		test >>= 1;
//		if (ADC0832_DAT1)test|=0x80;
//		else test|=0x00;
//		_nop_();
//		ADC0832_SCL1 = 1;
//		_nop_();
//		ADC0832_SCL1 = 0;
//	}
//	if (adval == test)dat = test;//比较前8位与后8位的值，如果不相同舍去。若一直出现显示为零，请将该行去掉
//	nop_();
//	ADC0832_CS1 = 1;	//释放ADC0832
//	ADC0832_DAT1 = 1;
//	ADC0832_SCL1 = 1;
//	return dat;
//}




//ADC转换
unsigned char ADC0832_Get(unsigned char CH)
{
	unsigned char i,test,adval;
	unsigned char dat = 0;	//AD值
	adval = 0x00;
	test = 0x00;

	ADC0832_SCL = 0;	//初始化
	ADC0832_DAT = 1;
	_nop_();
	ADC0832_CS = 0;
	_nop_();
	ADC0832_SCL = 1;
	_nop_();
	if ( CH==0 )	//通道选择
	{
		ADC0832_SCL = 0;
		ADC0832_DAT = 1;	//通道0的第一位
		_nop_();
		ADC0832_SCL = 1;
		_nop_();
		ADC0832_SCL = 0;
		ADC0832_DAT = 0;	//通道0的第二位
		_nop_();
		ADC0832_SCL = 1;
		_nop_();
	}else
	{
		ADC0832_SCL = 0;
		ADC0832_DAT = 1;	//通道1的第一位
		_nop_();
		ADC0832_SCL = 1;
		_nop_();
		ADC0832_SCL = 0;
		ADC0832_DAT = 1;	//通道1的第二位
		_nop_();
		ADC0832_SCL = 1;
		_nop_();
	}

	ADC0832_SCL = 0;
	ADC0832_DAT = 1;
	for( i = 0;i < 8;i++ )	//读取前8位的值
	{
		_nop_();
		adval <<= 1;
		ADC0832_SCL = 1;
		_nop_();
		ADC0832_SCL = 0;
		if (ADC0832_DAT)adval |= 0x01;
		else adval |= 0x00;
	}
	for (i = 0; i < 8; i++)	//读取后8位的值
	{
		test >>= 1;
		if (ADC0832_DAT)test|=0x80;
		else test|=0x00;
		_nop_();
		ADC0832_SCL = 1;
		_nop_();
		ADC0832_SCL = 0;
	}
	if (adval == test)dat = test;//比较前8位与后8位的值，如果不相同舍去。若一直出现显示为零，请将该行去掉
	nop_();
	ADC0832_CS = 1;	//释放ADC0832
	ADC0832_DAT = 1;
	ADC0832_SCL = 1;
	return dat;
}



