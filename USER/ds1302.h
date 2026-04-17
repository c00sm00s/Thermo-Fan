#ifndef __DS1302_H__
#define __DS1302_H__

#include "main.h"
#include "reg52.h"

//初始时间
extern uchar time_buf[8];//初始时间2010年6月1号23点59分55秒 星期二



//DS1302引脚定义
sbit DS1302_RST	=	P3^4;
sbit DS1302_IO	=	P3^5;
sbit DS1302_SCK	=	P3^6;
//DS1302地址定义
#define ds1302_sec_add			0x80		//秒数据地址
#define ds1302_min_add			0x82		//分数据地址
#define ds1302_hr_add				0x84		//时数据地址
#define ds1302_date_add			0x86		//日数据地址
#define ds1302_month_add		0x88		//月数据地址
#define ds1302_day_add			0x8a		//星期数据地址
#define ds1302_year_add			0x8c		//年数据地址
#define ds1302_control_add	0x8e		//控制数据地址
#define ds1302_charger_add	0x90 				 
#define ds1302_clkburst_add	0xbe


//DS1302初始化函数
void ds1302_init(void);
//向DS1302写入一字节数据
void ds1302_write_byte(uchar addr, uchar d);
//从DS1302读出一字节数据
uchar ds1302_read_byte(uchar addr);
//向DS302写入时钟数据
void ds1302_write_time(void);
//从DS302读出时钟数据
void ds1302_read_time(void);




#endif


