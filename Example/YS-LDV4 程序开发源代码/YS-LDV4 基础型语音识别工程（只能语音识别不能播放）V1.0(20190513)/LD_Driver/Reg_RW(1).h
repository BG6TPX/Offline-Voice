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
/*************端口信息********************
 * 接线说明
 LD3320接口 	  STM32接口
 * RST              PB6
 * CS   	        PB8
 * WR/SPIS          PB9
 * P2/SDCK          PB3
 * P1/SDO           PB4
 * P0/SDI           PB5
 * IRQ              PC1
 * A0		        PB7
 * RD               PA0
 --------------------------
 * K1               RST （复位键）
 * K2               PA1 （U盘处罚按键）
 * K3               PA2 （未定义功能）

 * LED1             PC4 （流水灯）
 * LED2             PC2 （流水灯）
 * LED3             PC3 （流水灯） 
 * LED4             PC0 （流水灯） 
*****************************************/

// Reg_RW.h  读写LD3320芯片的寄存器，共有四种方法。
#ifndef REG_RW_H
#define REG_RW_H

#define uint8 unsigned char
#define uint16 unsigned int
#define uint32 unsigned long


#define LD_RST_H() GPIO_SetBits(GPIOB, GPIO_Pin_6)
#define LD_RST_L() GPIO_ResetBits(GPIOB, GPIO_Pin_6)

#define LD_CS_H()	GPIO_SetBits(GPIOB, GPIO_Pin_8)
#define LD_CS_L()	GPIO_ResetBits(GPIOB, GPIO_Pin_8)

#define LD_SPIS_H()  GPIO_SetBits(GPIOB, GPIO_Pin_9)
#define LD_SPIS_L()  GPIO_ResetBits(GPIOB, GPIO_Pin_9)



/****************************************************************
函数名： LD_WriteReg
功能：写LD3320芯片的寄存器
参数：  address, 8位无符号整数，地址
		dataout，8位无符号整数，要写入的数据
返回值：无
****************************************************************/ 
void LD_WriteReg( unsigned char address, unsigned char dataout );

/****************************************************************
函数名： LD_ReadReg
功能：读LD3320芯片的寄存器
参数：  address, 8位无符号整数，地址
返回值：8位无符号整数，读取的结果
****************************************************************/ 
unsigned char LD_ReadReg( unsigned char address );



#endif
