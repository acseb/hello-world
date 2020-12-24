/**
* @file:main.c
* @copyright:Copyright 2020-2021 SGMW. Co. Ltd. All Rights Reserved.
* @brief:
* @detail:
* @author:郭轩铭
* @date:2020-11-27
* @version:v1.0
* @record:修改记录
*/
#include "reg52.h"			 //此文件中定义了单片机的一些特殊功能寄存器
#include "num.h"
#include "intrins.h"
#include "uart.h"

u8 code smgduan[16]= {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
                      0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71
                     };//显示0~F的值

u8 light[3] = {0,0,0};

u8 num = 0;

u8 ReadBuff[10];

sbit echo = P1^1;
sbit trig = P1^0;

u16   timeh,timel,time = 0;

/**
* @brief:中断器初始化
* @Name:Timer0Init
* @author: 郭轩铭
* @Data:2020-11-27
* @version:V1.0
* @param:空
* @return:空
**/
void Timer0Init(void)
{
    TMOD = 0x09;
    TH0=0; //设置初值
    TL0=0;
    EA = 1;
    ET0 = 1;
}

/**
* @brief:中断函数
* @Name:Timer0
* @author: 郭轩铭
* @Data:2020-11-27
* @version:V1.0
* @param:空
* @return:空
**/
void Timer0Initrupt(void) interrupt 1
{
    TH0=0; //设置初值
    TL0=0;
}

/**
* @brief:计算距离
* @Name:Conut
* @author: 郭轩铭
* @Data:2020-12-15
* @version:V1.0
* @param:空
* @return:空
**/
void Conut(void)
{
    time=TH0*256+TL0;
    TH0=0;
    TL0=0;
    num=(time*1.7)/100; //算出来是CM
    if(num >= 500)
      num = 500;
    Cal();
}

/**
* @brief:主函数
* @Name:main
* @author: 郭轩铭
* @Data:2020-11-27
* @version:V1.0
* @param:空
* @return:空
**/
void main()
{
    Timer0Init();
    InitConfig();
    while(1)
    {
        trig=1;
        _nop_();
        _nop_();
        _nop_();
        _nop_();
        _nop_();
        _nop_();
        trig=0;
        while(!echo); //当RX为零时等待
        TR0=1; //开启计数
        while(echo); //当RX为1计数并等待
        TR0=0; //关闭计数
        Conut(); //计算
        Delay(280); //延时，反正发射信号对回响信号的影响
        UartSendStr(ReadBuff);
        DisplayNum();
    }
}
