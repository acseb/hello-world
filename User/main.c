/**
* @file:main.c
* @copyright:Copyright 2020-2021 SGMW. Co. Ltd. All Rights Reserved.
* @brief:玩具炸弹
* @detail:
* @author:郭轩铭
* @date:2020-11-27
* @version:v1.0
* @record:修改记录
*/

#include <reg52.h>
#include <intrins.h>
#include "key.h"
#include "light.h"
#include "uart.h"
#include "i2c.h"


u8 code lightsmg[18] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
                        0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x40,0x00
                       };//显示0~F的值

u8 light[3] = {2,2,2};

u8 i;

int datCount = 0;

u8 temp[BUFFSIZE];
u8 speed[BUFFSIZE];
u8 mode[BUFFSIZE];
u8 tos[BUFFSIZE];



/**
* @brief:清空数组
* @Name:ClearArray
* @author: 郭轩铭
* @Data:2020-12-16
* @version:V1.0
* @param:空
* @return:空
**/
void ClearArray(u8 table[])
{
    for(i = 0;i < BUFFSIZE;i++)
        table[i] = '\0';
}

void SaveDataToArray(u8 table[])
{
    for(i = 0;i < strlen(temp);i ++)
        table[i] = temp[i]; 
    for(i = strlen(temp);i < BUFFSIZE;i++)
        table[i] = '\0';
    UartSendStr(table);
    UartSendByte('\r');
    UartSendByte('\n');
}


void InputData(u8 flag)
{

    if(flag == 1)
    {
        UartSendStr(CAR_SPEED);
        SaveDataToArray(speed);
    }
    else if(flag == 2)
    {
        UartSendStr(SEAT_BELT_MODE);
        SaveDataToArray(mode);
    }
    else if(flag == 3)
    {
        UartSendStr(TOS);
        SaveDataToArray(tos);
    }
}



/**
* @brief:主函数
* @Name:main
* @author: 郭轩铭
* @Data:2020-11-27
* @version:V1.0
* @param:
* @return:
**/
void main()
{
    u8 flag = 0;
    //配置初始化
    InitConfig();
//    ClearArray(speed);
//    ClearArray(mode);
//    ClearArray(tos);
    
    while(1)
    {
        //按键等待检测
        SavePress();
        ReadPress();
        //UartSendStr(datCount);
        //Delay(5000);
        if(datCount == -1)
        {
            UartSendStr(ERROR);
            //加入换行
            UartSendByte('\r');
            UartSendByte('\n');
            datCount = 0;
        }
        else if(datCount > 0)
        {
            flag++;
            InputData(flag);
            ClearArray(temp);
            datCount = 0;
            if(flag == 3)
                flag = 0;
        }
//        light[2] = tos[2];
//        light[1] = mode[1];
//        light[0] = speed[0];
        //显示动态数码管
        DisplayNum();
    }
}
