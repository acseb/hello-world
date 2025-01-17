/**
* @file:key.c
* @copyright:Copyright 2020-2021 SGMW. Co. Ltd. All Rights Reserved.
* @brief:按键功能函数集合
* @detail:
* @author:郭轩铭
* @date:2020-11-27
* @version:v1.0
* @record:修改记录
*/
#include "key.h"

/**
* @brief:延时函数
* @Name:Delay
* @author: 郭轩铭
* @Data:2020-11-27
* @version:V1.0
* @param:i 延迟时长
* @return:空
**/
void Delay(u16 i)
{
    while(i--);
}


/**
* @brief:把数组数据存入E2
* @Name:WriteData
* @author: 郭轩铭
* @Data:2020-12-16
* @version:V1.0
* @param:空
* @return:空
**/
void WriteData(u8 table[],u8 len)
{
    for(i=0; i<strlen(table); i++)
    {
        At24c02Write(5*i+2+len,table[i]);	  //在对应的地址中放入对应的字符
        Delay(100);
    }
}

/**
* @brief:保存按键
* @Name:SavePress
* @author: 郭轩铭
* @Data:2020-12-16
* @version:V1.0
* @param:空
* @return:空
**/
void SavePress()
{
    if(key4 == 0)
    {
        Delay(2000);
        if(key4 == 0)
        {
            WriteData(speed,0);
            WriteData(mode,17);
            WriteData(tos,33);
        }
    }
}

/**
* @brief:从E2中读取数据
* @Name:ReadData
* @author: 郭轩铭
* @Data:2020-12-16
* @version:V1.0
* @param:空
* @return:空
**/
void ReadData(u8 table[],u8 len)
{
    for(i=0; i<BUFFSIZE; i++)
    {
        table[i]= At24c02Read(5*i+2+len);
//神奇的一段代码，数组内赋值不需要+‘0’，但直接初始化的时候需要
//        if(len == 0)                        
//            UartSendByte(table[i]+'0');
//        else
        UartSendByte(table[i]);
        Delay(100);
    }
    UartSendByte('\r');
    UartSendByte('\n');
}

/**
* @brief:读取按键
* @Name:ReadPress
* @author: 郭轩铭
* @Data:2020-12-16
* @version:V1.0
* @param:空
* @return:空
**/
void ReadPress()
{
    if(key3 == 0)
    {
        Delay(2000);
        if(key3 == 0)
        {
            UartSendStr(CAR_SPEED);
            ReadData(speed,0);
            UartSendStr(SEAT_BELT_MODE);
            ReadData(mode,17);
            UartSendStr(TOS);
            ReadData(tos,33);
        }
    }
}

