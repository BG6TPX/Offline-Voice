/***************************飞音云电子****************************
**  工程名称：YS-LDV3语音识别开发板驱动程序
**	CPU: STC11L08XE
**	晶振：22.1184MHZ
**	波特率：9600 bit/S
**	配套产品信息：YS-LDV3语音识别开发板
**                http://yuesheng001.taobao.com
**  作者：zdings
**  联系：751956552@qq.com
**  修改日期：2014.08.16
**  说明：口令模式： 即每次识别时都需要说“小石头”这个口令 ，才能够进行下一级的识别
/***************************飞音云电子******************************/
#include "config.h"
/************************************************************************************/
//	nAsrStatus 用来在main主程序中表示程序运行的状态，不是LD3320芯片内部的状态寄存器
//	LD_ASR_NONE:		表示没有在作ASR识别
//	LD_ASR_RUNING：		表示LD3320正在作ASR识别中
//	LD_ASR_FOUNDOK:		表示一次识别流程结束后，有一个识别结果
//	LD_ASR_FOUNDZERO:	表示一次识别流程结束后，没有识别结果
//	LD_ASR_ERROR:		表示一次识别流程中LD3320芯片内部出现不正确的状态
/***********************************************************************************/
uint8 idata nAsrStatus=0;	
void MCU_init(); 
void ProcessInt0(); //识别处理函数
void delay(unsigned long uldata);
void User_handle(uint8 dat);//用户执行操作函数
void Delay200ms();
void Led_test(void);//单片机工作指示
void Led_test1(void);
uint8_t G0_flag=DISABLE;//运行标志，ENABLE:运行。DISABLE:禁止运行 

sbit LED1=P4^0;//信号指示灯1
sbit LED2=P2^2;//信号指示灯2
sbit LED3=P4^1;//信号指示灯3

sbit key1=P4^2;//按键1
sbit key2=P4^3;//按键2
sbit key3=P3^4;//按键3

//定义P1端口
sbit CH0=P1^0;
sbit CH1=P1^1;
sbit CH2=P1^2;
sbit CH3=P1^3;
sbit CH4=P1^4;
sbit CH5=P1^5;
sbit CH6=P1^6;
sbit CH7=P1^7;
/***********************************************************
* 名    称： void  main(void)
* 功    能： 主函数	程序入口
* 入口参数：  
* 出口参数：
* 说    明： 					 
* 调用方法： 
**********************************************************/ 
void  main(void)
{
	uint8 idata nAsrRes;
	uint8 i=0;
	MCU_init();
	Led_test();
	LD_Reset(); //语音芯片复位
	UartIni(); /*串口初始化*/
	nAsrStatus = LD_ASR_NONE;		//	初始状态：没有在作ASR
	
	#ifdef TEST	
    PrintCom("一级口令：小石头\r\n"); /*text.....*/
	PrintCom("二级口令：1、代码测试\r\n"); /*text.....*/
	PrintCom("	2、开发板验证\r\n"); /*text.....*/
	PrintCom("	3、开灯\r\n"); /*text.....*/
	PrintCom("	4、关灯\r\n"); /*text.....*/
	PrintCom("  5、北京\r\n"); /*text.....*/
	PrintCom("	6、上海\r\n"); /*text.....*/
	PrintCom("	7、广州\r\n"); /*text.....*/
	#endif

	while(1)
	{
		switch(nAsrStatus)
		{
			case LD_ASR_RUNING:
			case LD_ASR_ERROR:		
				break;
			case LD_ASR_NONE:
			{
				nAsrStatus=LD_ASR_RUNING;
				if (RunASR()==0)	/*	启动一次ASR识别流程：ASR初始化，ASR添加关键词语，启动ASR运算*/
				{
					nAsrStatus = LD_ASR_ERROR;
				}
				break;
			}
			case LD_ASR_FOUNDOK: /*	一次ASR识别流程结束，去取ASR识别结果*/
			{				
				nAsrRes = LD_GetResult();		/*获取结果*/
				User_handle(nAsrRes);//用户执行函数 
				nAsrStatus = LD_ASR_NONE;
				break;
			}
			case LD_ASR_FOUNDZERO:
			default:
			{
				nAsrStatus = LD_ASR_NONE;
				break;
			}
		}// switch	 			
		
		//按键功能演示测试。。。。。。用于测试按键是否正常
		if(key1==0 || key2==0 || key3==0)
		{
		   Led_test1();
		}
	}// while

}
/***********************************************************
* 名    称： 	 LED灯测试
* 功    能： 单片机是否工作指示
* 入口参数： 无 
* 出口参数：无
* 说    明： 					 
**********************************************************/
void Led_test(void)
{
	Delay200ms();Delay200ms();
	LED1=0;LED2=0;LED3=0;
	Delay200ms();Delay200ms();
	LED1=1;LED2=1;LED3=1;
	Delay200ms();Delay200ms();
	LED1=0;LED2=0;LED3=0;
	Delay200ms();Delay200ms();
	LED1=1;LED2=1;LED3=1;
	Delay200ms();Delay200ms();
	LED1=0;LED2=0;LED3=0;
}
// 用于指示是否识别成功
void Led_test1(void)
{
	LED1=1;LED2=0;LED3=0;
	Delay200ms();
	LED1=0;LED2=1;LED3=0;
	Delay200ms();
	LED1=0;LED2=0;LED3=1;
	Delay200ms();
	LED1=0;LED2=0;LED3=0;
}


/***********************************************************
* 名    称： void MCU_init()
* 功    能： 单片机初始化
* 入口参数：  
* 出口参数：
* 说    明： 					 
* 调用方法： 
**********************************************************/ 
void MCU_init()
{
	P0 = 0xff;
	
	P2 = 0xff;
	P3 = 0xff;
	P4 = 0xff;
	
	P1M1=0X00;P1M0=0XFF;//设置P1端口为推完输出，提高IO口电流。//设置方法参考单片机数据手册第67页。
	P1 = 0x00;//使P1默认为低电平。

	IE0=1;
	EX0=1;
	EA=1;
}
/***********************************************************
* 名    称：	延时函数
* 功    能：
* 入口参数：  
* 出口参数：
* 说    明： 					 
* 调用方法： 
**********************************************************/ 
void Delay200us()		//@22.1184MHz
{
	unsigned char i, j;
	_nop_();
	_nop_();
	i = 5;
	j = 73;
	do
	{
		while (--j);
	} while (--i);
}

void  delay(unsigned long uldata)
{
	unsigned int j  =  0;
	unsigned int g  =  0;
	while(uldata--)
	Delay200us();
}

void Delay200ms()		//@22.1184MHz
{
	unsigned char i, j, k;

	i = 17;
	j = 208;
	k = 27;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

/***********************************************************
* 名    称： 中断处理函数
* 功    能：
* 入口参数：  
* 出口参数：
* 说    明： 					 
* 调用方法： 
**********************************************************/ 
void ExtInt0Handler(void) interrupt 0  
{ 	
	ProcessInt0();				
}
/***********************************************************
* 名    称：用户执行函数 
* 功    能：识别成功后，执行动作可在此进行修改 
* 入口参数： 无 
* 出口参数：无
* 说    明： 					 
**********************************************************/
void 	User_handle(uint8 dat)
{
     //UARTSendByte(dat);//串口识别码（十六进制）
		 if(0==dat)
		 {
		  	G0_flag=ENABLE;
			LED1=1;LED2=1;LED3=1;	 //指示灯全部点亮，提示口令识别成功
			PrintCom("收到\r\n"); /*text.....*/
		 }
		 else if(ENABLE==G0_flag)
		 {	
		 		G0_flag=DISABLE;
			 switch(dat)		   /*对结果执行相关操作,客户可删除Printcom 串口输出语句替换为其他需要控制的代码*/
			  {
				  case CODE_DMCS:			/*命令“测试”*/
						PrintCom("“代码测试”命令识别成功\r\n"); /*text.....*/
						CH0=1;//使P1.0端口输出高电平
						Led_test1();//指示灯提示识别完成
													 break;
					case CODE_KFBYZ:	 /*命令“全开”*/
						PrintCom("“开发板验证”命令识别成功\r\n"); /*text.....*/
						CH1=1;//使P1.1端口输出高电平
						Led_test1();//指示灯提示识别完成
													 break;
					case CODE_KD:		/*命令“复位”*/				
						PrintCom("“开灯”命令识别成功\r\n"); /*text.....*/
						CH2=1;//使P1.2端口输出高电平
						Led_test1();//指示灯提示识别完成
													break;
					case CODE_GD:		/*命令“复位”*/				
						CH2=0;//使P1.2端口输出低电平
						PrintCom("“关灯”命令识别成功\r\n"); /*text.....*/
						Led_test1();//指示灯提示识别完成
													break;
					case CODE_BJ:		/*命令“复位”*/										
						PrintCom("“北京”命令识别成功\r\n"); /*text.....*/
						CH3=1;//使P1.3端口输出高电平
						Led_test1();//指示灯提示识别完成
													break;
					case CODE_SH:		/*命令“复位”*/				
						PrintCom("“上海”命令识别成功\r\n"); /*text.....*/
						CH4=1;//使P1.4端口输出高电平
						Led_test1();//指示灯提示识别完成
													break;
					case CODE_GZ:		/*命令“复位”*/				
						PrintCom("“广州”命令识别成功\r\n"); /*text.....*/
						CH5=1;//使P1.5端口输出高电平
						Led_test1();//指示灯提示识别完成
													break;																											
						default:PrintCom("请重新识别发口令\r\n"); /*text.....*/break;
				}	
			}	
			else 	
			{
				PrintCom("请说出一级口令\r\n"); /*text.....*/	
			}
}	 
