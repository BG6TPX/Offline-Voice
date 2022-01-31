/***************************飞音云电子****************************
**  文件名称：LDV4语音识别开发板 基础版驱动程序
**	CPU: STM32f103RCT6
**	晶振：8MHZ
**	波特率：9600 bit/S
**	配套产品信息：YS-LDV4语音识别开发板
**                http://yuesheng001.taobao.com
**  作者：zdings
**  联系：751956552@qq.com
**  修改日期：2014.09.15
**  说明：本程序 具备语音识别、串口通信、开发板基本功能演示。
** 说明：本程序修改于 ICRoute公司 配套的源程序，版权归其所有。
***************************飞音云电子******************************/
#ifndef __LEDTEST_H__
#define __LEDTEST_H__


void Glide_LED(void);
void Board_text(uint8 Code_Val);
void LED_gpio_cfg(void);





#endif
