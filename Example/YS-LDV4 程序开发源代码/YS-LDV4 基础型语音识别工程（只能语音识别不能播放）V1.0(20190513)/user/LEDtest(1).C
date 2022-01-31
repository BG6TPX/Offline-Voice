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
#include "includes.h"

extern void PrintComBit(USART_TypeDef* USARTx, uint8_t Data);

#define LED4_H()	GPIO_SetBits(GPIOC, GPIO_Pin_0)
#define LED4_L()	GPIO_ResetBits(GPIOC, GPIO_Pin_0)
#define LED2_H()	GPIO_SetBits(GPIOC, GPIO_Pin_2)
#define LED2_L()	GPIO_ResetBits(GPIOC, GPIO_Pin_2)
#define LED3_H()	GPIO_SetBits(GPIOC, GPIO_Pin_3)
#define LED3_L()	GPIO_ResetBits(GPIOC, GPIO_Pin_3)
#define LED1_H()	GPIO_SetBits(GPIOC, GPIO_Pin_4)
#define LED1_L()	GPIO_ResetBits(GPIOC, GPIO_Pin_4)
#define C6_H()	GPIO_SetBits(GPIOC, GPIO_Pin_6)
#define C6_L()	GPIO_ResetBits(GPIOC, GPIO_Pin_6)


/***********************************************************
* 名    称：void LED_gpio_cfg(void)
* 功    能：LED端口配置
* 入口参数：  
* 出口参数：
* 说    明：
* 调用方法： 
**********************************************************/ 
void LED_gpio_cfg(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_6;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
		GPIO_SetBits(GPIOC,GPIO_Pin_0);
		GPIO_SetBits(GPIOC,GPIO_Pin_2);
		GPIO_SetBits(GPIOC,GPIO_Pin_3);
		GPIO_SetBits(GPIOC,GPIO_Pin_4);
		C6_L();
}


/***********************************************************
* 名    称：void Delayms(uint16 i)
* 功    能： 延时n毫秒
* 入口参数：  
* 出口参数：
* 说    明： 					 
* 调用方法：
**********************************************************/ 
void Delayms(uint16 i)
{
	unsigned char a,b;
	for(;i>0;i--)
	        for(b=4;b>0;b--)
	            for(a=113;a>0;a--);	

}

/***********************************************************
* 名    称：void Glide_LED(void)
* 功    能： 实现流水灯功能
* 入口参数：  
* 出口参数：
* 说    明： 					 
* 调用方法： 
**********************************************************/ 
void Glide_LED(void)
{
	LED1_L();LED2_H();LED3_H();LED4_H();		    /*流水灯*/
	sys_delay_ms(150);
	LED1_H();LED2_L();LED3_H();LED4_H();
	sys_delay_ms(150);		  
	LED1_H();LED2_H();LED3_L();LED4_H();
	sys_delay_ms(150);		  
	LED1_H();LED2_H();LED3_H();LED4_L();
	sys_delay_ms(150);		  
	LED1_H();LED2_H();LED3_H();LED4_H();
	sys_delay_ms(150);		  
	LED1_H();LED2_H();LED3_H();LED4_L();
	sys_delay_ms(150);		  
	LED1_H();LED2_H();LED3_L();LED4_H();
	sys_delay_ms(150);
	LED1_H();LED2_L();LED3_H();LED4_H();
	sys_delay_ms(150);
	LED1_L();LED2_H();LED3_H();LED4_H();
	sys_delay_ms(150);
	LED1_H();LED2_H();LED3_H();LED4_H();

}

/***********************************************************
* 名    称：void Board_text(uint8 Code_Val)
* 功    能：	开发板测试程序
* 入口参数：  
* 出口参数：
* 说    明： 该函数为用户对识别结果的一个操作，例如识别到开灯后
			识别码为“CODE_DD”，接着要做什么事情就在里面写入程序。					 
* 调用方法： 
**********************************************************/ 
void Board_text(uint8 Code_Val)
{																					 	 
	 switch(Code_Val)		  
	  {
		  case CODE_DD:	LED1_L();          /*打开电灯*/
		  break;
		  case CODE_GD: LED1_H();		   /*关闭电灯*/
		  break;
		  case CODE_QDD: LED1_L();LED2_L();LED3_L();LED4_L();		   /*全部灯打开*/
		  break;
		  case CODE_DG:	LED1_H();LED2_H();LED3_H();LED4_H();		   /*全部关闭*/
		  break;
		  case CODE_LSD:	LED1_L();LED2_H();LED3_H();LED4_H();		    /*流水灯*/
							sys_delay_ms(150);
							LED1_H();LED2_L();LED3_H();LED4_H();
							sys_delay_ms(150);		  
							LED1_H();LED2_H();LED3_L();LED4_H();
							sys_delay_ms(150);		  
							LED1_H();LED2_H();LED3_H();LED4_L();
							sys_delay_ms(150);		  
							LED1_H();LED2_H();LED3_H();LED4_H();
							sys_delay_ms(150);		  
							LED1_H();LED2_H();LED3_H();LED4_L();
							sys_delay_ms(150);		  
							LED1_H();LED2_H();LED3_L();LED4_H();
							sys_delay_ms(150);
							LED1_H();LED2_L();LED3_H();LED4_H();
							sys_delay_ms(150);
							LED1_L();LED2_H();LED3_H();LED4_H();
							sys_delay_ms(150);
							LED1_H();LED2_H();LED3_H();LED4_H();

		  break;
		  case CODE_SSD:		   /*闪烁灯*/
		  				LED1_L();LED2_L();LED3_L();LED4_L();
						sys_delay_ms(150);
						LED1_H();LED2_H();LED3_H();LED4_H();
						sys_delay_ms(150);
		  				LED1_L();LED2_L();LED3_L();LED4_L();
						sys_delay_ms(150);
						LED1_H();LED2_H();LED3_H();LED4_H();
		  break;				  
		  case CODE_DDR: C6_H();		   /*打开继电器*/
		  break;
		  case CODE_RDD: C6_H();sys_delay_ms(1000);C6_L();		   /*继电器点动*/
		  break;
		  case CODE_PLAY:		    /*播放歌曲*/
		  break;
		  case CODE_NAME:		   /*你叫什么名字*/
		  break;											   
		  case CODE_DO:			   /*你会做什么*/
		  break;
		  default:break;
		}	
}
