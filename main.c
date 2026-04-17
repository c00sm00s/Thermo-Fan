#include "reg52.h"
#include "main.h"
#include "delay.h"
#include "lcd.h"
#include "uart1.h"
#include "intrins.h"
#include "ds18.h"

//按键控制脚
sbit KEY1=P2^0;//KEY1
sbit KEY2=P2^1;//KEY2
sbit KEY3=P2^2;//KEY3
sbit KEY4=P2^3;//KEY4

sbit FS    =P1^1; //风扇

u32 WD=0;         //当前温度
u32 WDYZ=251;     //温度阈值 25.1℃
u32 last_WD=0;
bit  first_read=1; // 第一次采集标志

u8  LW=0;
u8 mode=0;
u8 u2_rx2=0;

//==================== PID 参数 ====================
float pid_kp  = 0.8f;
float pid_ki  = 0.1f;
float pid_kd  = 0.5f;

int  error;
int  last_error;
float integral;
int  pwm_out;
int  derivative;

u8  ks = 0;
u16 zs = 0;

#define FOSC 11059200L
#define T1MS (65536-FOSC/12/1000)

// 串口中断
void Uart_Isr() interrupt 4
{
	if (RI)
	{
		RI=0;
		u2_rx2 = SBUF;
	}
	if (TI){TI=0;}
}

// PWM 0~100
void tm0_isr() interrupt 1
{
	TL0 = T1MS;
	TH0 = T1MS >> 8;
	zs++;
	if(zs >= 100) zs = 0;
	if(ks > zs) FS = 1;
	else FS = 0;
}

// 显示
void show(void)
{
   LCD_ShowNmber(11,0,WD/10,2);
   LCD_ShowNmber(14,0,WD%10,1);
   LCD_ShowNmber(11,1,WDYZ/10,2);
   LCD_ShowNmber(14,1,WDYZ%10,1);
   LCD_ShowNmber( 3,1,ks,3);
}

//==================== PID 计算 ====================
void PID_Calc(void)
{
	error = WD - WDYZ;

	if(error > 0)
		integral += error;
	else
		integral = 0;

	if(integral > 200) integral = 200;
	if(integral < 0)   integral = 0;

	derivative = error - last_error;

	pwm_out = pid_kp * error
	        + pid_ki * integral
	        + pid_kd * derivative;

	if(pwm_out < 0)   pwm_out = 0;
	if(pwm_out > 100) pwm_out = 100;

	last_error = error;
	ks = pwm_out;
}

//==================== 最终正确温度限制 ====================
void Limit_Temperature(void)
{
    // 第一次采集温度：不限制，直接用真实温度（关键！）
    if(first_read)
    {
        first_read = 0;
        last_WD = WD;
        return;
    }

    // 只有非第一次，才做温度变化限制
    if(WD > last_WD + 10)    // 上升超过2度
    {
        WD = last_WD + 10;
    }
    else if(WD < last_WD - 10) // 下降超过2度
    {
        WD = last_WD - 10;
    }

    last_WD = WD;
}

//==================== 主函数 ====================
int main(void)
{
	u16 SYSTICK=0;

	TMOD = 0x01;
	TL0 = T1MS;
	TH0 = T1MS >> 8;
	TR0 = 1;
	ET0 = 1;
	EA  = 1;

	delay_ms(100);
	UartInit();
	delay1(100);
	LCD_init();
	delay1(100);

	LCD_Show(0,0,"temperature00.0 ");
	LCD_Show(0,1,"DW:0       00.0 ");

	while(1)
	{
		delay1(1);
		SYSTICK++;

		if(SYSTICK % 300 == 0)
		{
			WD = getTmpValue();

			Limit_Temperature(); // 温度平滑限制

			PID_Calc();

			show();
		}

		// 按键3 +
		if(KEY3==0)
		{
			delay1(5);
			if(KEY3==0)
			{
				WDYZ++;
				show();
				while(KEY3==0);
			}
		}

		// 按键4 -
		if(KEY4==0)
		{
			delay1(5);
			if(KEY4==0)
			{
				WDYZ--;
				show();
				while(KEY4==0);
			}
		}

		if(KEY1==0){delay1(5);if(KEY1==0)while(KEY1==0);}
		if(KEY2==0){delay1(5);if(KEY2==0)while(KEY2==0);}
	}
}


