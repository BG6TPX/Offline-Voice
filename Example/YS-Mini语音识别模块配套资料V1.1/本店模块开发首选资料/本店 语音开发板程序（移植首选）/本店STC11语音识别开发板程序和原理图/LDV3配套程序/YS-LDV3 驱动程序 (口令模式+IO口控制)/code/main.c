/***************************�����Ƶ���****************************
**  �������ƣ�YS-LDV3����ʶ�𿪷�����������
**	CPU: STC11L08XE
**	����22.1184MHZ
**	�����ʣ�9600 bit/S
**	���ײ�Ʒ��Ϣ��YS-LDV3����ʶ�𿪷���
**                http://yuesheng001.taobao.com
**  ���ߣ�zdings
**  ��ϵ��751956552@qq.com
**  �޸����ڣ�2014.08.16
**  ˵��������ģʽ�� ��ÿ��ʶ��ʱ����Ҫ˵��Сʯͷ��������� �����ܹ�������һ����ʶ��
/***************************�����Ƶ���******************************/
#include "config.h"
/************************************************************************************/
//	nAsrStatus ������main�������б�ʾ�������е�״̬������LD3320оƬ�ڲ���״̬�Ĵ���
//	LD_ASR_NONE:		��ʾû������ASRʶ��
//	LD_ASR_RUNING��		��ʾLD3320������ASRʶ����
//	LD_ASR_FOUNDOK:		��ʾһ��ʶ�����̽�������һ��ʶ����
//	LD_ASR_FOUNDZERO:	��ʾһ��ʶ�����̽�����û��ʶ����
//	LD_ASR_ERROR:		��ʾһ��ʶ��������LD3320оƬ�ڲ����ֲ���ȷ��״̬
/***********************************************************************************/
uint8 idata nAsrStatus=0;	
void MCU_init(); 
void ProcessInt0(); //ʶ������
void delay(unsigned long uldata);
void User_handle(uint8 dat);//�û�ִ�в�������
void Delay200ms();
void Led_test(void);//��Ƭ������ָʾ
void Led_test1(void);
uint8_t G0_flag=DISABLE;//���б�־��ENABLE:���С�DISABLE:��ֹ���� 

sbit LED1=P4^0;//�ź�ָʾ��1
sbit LED2=P2^2;//�ź�ָʾ��2
sbit LED3=P4^1;//�ź�ָʾ��3

sbit key1=P4^2;//����1
sbit key2=P4^3;//����2
sbit key3=P3^4;//����3

//����P1�˿�
sbit CH0=P1^0;
sbit CH1=P1^1;
sbit CH2=P1^2;
sbit CH3=P1^3;
sbit CH4=P1^4;
sbit CH5=P1^5;
sbit CH6=P1^6;
sbit CH7=P1^7;
/***********************************************************
* ��    �ƣ� void  main(void)
* ��    �ܣ� ������	�������
* ��ڲ�����  
* ���ڲ�����
* ˵    ���� 					 
* ���÷����� 
**********************************************************/ 
void  main(void)
{
	uint8 idata nAsrRes;
	uint8 i=0;
	MCU_init();
	Led_test();
	LD_Reset(); //����оƬ��λ
	UartIni(); /*���ڳ�ʼ��*/
	nAsrStatus = LD_ASR_NONE;		//	��ʼ״̬��û������ASR
	
	#ifdef TEST	
    PrintCom("һ�����Сʯͷ\r\n"); /*text.....*/
	PrintCom("�������1���������\r\n"); /*text.....*/
	PrintCom("	2����������֤\r\n"); /*text.....*/
	PrintCom("	3������\r\n"); /*text.....*/
	PrintCom("	4���ص�\r\n"); /*text.....*/
	PrintCom("  5������\r\n"); /*text.....*/
	PrintCom("	6���Ϻ�\r\n"); /*text.....*/
	PrintCom("	7������\r\n"); /*text.....*/
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
				if (RunASR()==0)	/*	����һ��ASRʶ�����̣�ASR��ʼ����ASR��ӹؼ��������ASR����*/
				{
					nAsrStatus = LD_ASR_ERROR;
				}
				break;
			}
			case LD_ASR_FOUNDOK: /*	һ��ASRʶ�����̽�����ȥȡASRʶ����*/
			{				
				nAsrRes = LD_GetResult();		/*��ȡ���*/
				User_handle(nAsrRes);//�û�ִ�к��� 
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
		
		//����������ʾ���ԡ��������������ڲ��԰����Ƿ�����
		if(key1==0 || key2==0 || key3==0)
		{
		   Led_test1();
		}
	}// while

}
/***********************************************************
* ��    �ƣ� 	 LED�Ʋ���
* ��    �ܣ� ��Ƭ���Ƿ���ָʾ
* ��ڲ����� �� 
* ���ڲ�������
* ˵    ���� 					 
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
// ����ָʾ�Ƿ�ʶ��ɹ�
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
* ��    �ƣ� void MCU_init()
* ��    �ܣ� ��Ƭ����ʼ��
* ��ڲ�����  
* ���ڲ�����
* ˵    ���� 					 
* ���÷����� 
**********************************************************/ 
void MCU_init()
{
	P0 = 0xff;
	
	P2 = 0xff;
	P3 = 0xff;
	P4 = 0xff;
	
	P1M1=0X00;P1M0=0XFF;//����P1�˿�Ϊ������������IO�ڵ�����//���÷����ο���Ƭ�������ֲ��67ҳ��
	P1 = 0x00;//ʹP1Ĭ��Ϊ�͵�ƽ��

	IE0=1;
	EX0=1;
	EA=1;
}
/***********************************************************
* ��    �ƣ�	��ʱ����
* ��    �ܣ�
* ��ڲ�����  
* ���ڲ�����
* ˵    ���� 					 
* ���÷����� 
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
* ��    �ƣ� �жϴ�����
* ��    �ܣ�
* ��ڲ�����  
* ���ڲ�����
* ˵    ���� 					 
* ���÷����� 
**********************************************************/ 
void ExtInt0Handler(void) interrupt 0  
{ 	
	ProcessInt0();				
}
/***********************************************************
* ��    �ƣ��û�ִ�к��� 
* ��    �ܣ�ʶ��ɹ���ִ�ж������ڴ˽����޸� 
* ��ڲ����� �� 
* ���ڲ�������
* ˵    ���� 					 
**********************************************************/
void 	User_handle(uint8 dat)
{
     //UARTSendByte(dat);//����ʶ���루ʮ�����ƣ�
		 if(0==dat)
		 {
		  	G0_flag=ENABLE;
			LED1=1;LED2=1;LED3=1;	 //ָʾ��ȫ����������ʾ����ʶ��ɹ�
			PrintCom("�յ�\r\n"); /*text.....*/
		 }
		 else if(ENABLE==G0_flag)
		 {	
		 		G0_flag=DISABLE;
			 switch(dat)		   /*�Խ��ִ����ز���,�ͻ���ɾ��Printcom �����������滻Ϊ������Ҫ���ƵĴ���*/
			  {
				  case CODE_DMCS:			/*������ԡ�*/
						PrintCom("��������ԡ�����ʶ��ɹ�\r\n"); /*text.....*/
						CH0=1;//ʹP1.0�˿�����ߵ�ƽ
						Led_test1();//ָʾ����ʾʶ�����
													 break;
					case CODE_KFBYZ:	 /*���ȫ����*/
						PrintCom("����������֤������ʶ��ɹ�\r\n"); /*text.....*/
						CH1=1;//ʹP1.1�˿�����ߵ�ƽ
						Led_test1();//ָʾ����ʾʶ�����
													 break;
					case CODE_KD:		/*�����λ��*/				
						PrintCom("�����ơ�����ʶ��ɹ�\r\n"); /*text.....*/
						CH2=1;//ʹP1.2�˿�����ߵ�ƽ
						Led_test1();//ָʾ����ʾʶ�����
													break;
					case CODE_GD:		/*�����λ��*/				
						CH2=0;//ʹP1.2�˿�����͵�ƽ
						PrintCom("���صơ�����ʶ��ɹ�\r\n"); /*text.....*/
						Led_test1();//ָʾ����ʾʶ�����
													break;
					case CODE_BJ:		/*�����λ��*/										
						PrintCom("������������ʶ��ɹ�\r\n"); /*text.....*/
						CH3=1;//ʹP1.3�˿�����ߵ�ƽ
						Led_test1();//ָʾ����ʾʶ�����
													break;
					case CODE_SH:		/*�����λ��*/				
						PrintCom("���Ϻ�������ʶ��ɹ�\r\n"); /*text.....*/
						CH4=1;//ʹP1.4�˿�����ߵ�ƽ
						Led_test1();//ָʾ����ʾʶ�����
													break;
					case CODE_GZ:		/*�����λ��*/				
						PrintCom("�����ݡ�����ʶ��ɹ�\r\n"); /*text.....*/
						CH5=1;//ʹP1.5�˿�����ߵ�ƽ
						Led_test1();//ָʾ����ʾʶ�����
													break;																											
						default:PrintCom("������ʶ�𷢿���\r\n"); /*text.....*/break;
				}	
			}	
			else 	
			{
				PrintCom("��˵��һ������\r\n"); /*text.....*/	
			}
}	 
