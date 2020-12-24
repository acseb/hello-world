/**
* @file:light.c
* @copyright:Copyright 2020-2021 SGMW. Co. Ltd. All Rights Reserved.
* @brief:
* @detail:
* @author:郭轩铭
* @date:2020-11-27
* @version:v1.0
* @record:修改记录
*/
#include "light.h"
#include "key.h"


/**
* @brief:138译码器
* @Name:Drive138
* @author: 郭轩铭
* @Data:2020-11-27
* @version:V1.0
* @param:num 对应几号灯
* @return:空
**/
void Drive138(unsigned char num)
{
    LSA = num & 0x01;
    LSB = (num & 0x02) >> 1;
    LSC = (num & 0x04) >> 2;
}

/**
* @brief:显示动态数码管
* @Name:DisplayNum
* @author: 郭轩铭
* @Data:2020-11-27
* @version:V1.0
* @param: 空
* @return:空
**/
void DisplayNum()
{
    int i = 0;
    for(; i<3; i++)
    {
        Drive138(i);
        P0 = lightsmg[light[i]];
        Delay(200);
    }
}

/**
* @brief:定时中断函数
* @Name:Timer0
* @author: 郭轩铭
* @Data:2020-11-27
* @version:V1.0
* @param:空
* @return:空
**/
void Timer2_Server() interrupt 5
{
    static u16 i = 0;

    // T2定时器发生溢出中断时，需要用户自己清除溢出标记，而51的其他定时器是自动清除的
    TF2=0;

    //正常状态下更新数值
    if(i >= 16)
    {
        i=0;
    }
}
