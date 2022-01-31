

#ifndef REG_RW_H
#define REG_RW_H

//驱动端口定义
sbit RSTB=P3^3;	 /*复位端口*/
sbit CSB=P2^1;	 /*模块片选端口*/


//函数声明
void LD_WriteReg( unsigned char address, unsigned char dataout );
unsigned char LD_ReadReg( unsigned char address );


#endif
