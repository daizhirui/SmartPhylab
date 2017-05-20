/*----------------------------------------------------------------------
 * TITLE: Custom Functions
 * AUTHOR: DaiZhirui
 * DATE CREATED: 2017-04-29
 * FILENAME: ASTRO.c
 * PROJECT: M2 Laboratory
 * COPYRIGHT: DaiZhirui
 * DESCRIPTION:
 *    Custom functions based on reading and writing the registers of M2
 *    The functions in this repository is tested by DaiZhirui
 * MODIFICATION HISTORY:
 *  2017-04-29: added U0_Read, U0_Send, U0_LinMaster, U0_LinSlave
 *              U1_Read, U1_Send, U1_LinMaster, U1_LinSlave
 *  2017-05-14: added U0_SendString, U1_SendString; modified U0_Read, U1_Read
 *---------------------------------------------------------------------*/
#include "mcu.h"
/*********************Register-Address Definition**********************/
/*Uart0 Registers*/
#define U0_READ_REG             0x1f800000  //RX data read register
#define U0_BUSY_REG             0x1f800001  //Tx busy detect register
#define U0_WRITE_REG            0x1f800002  //Tx data write register
#define U0_CLRIRQ_REG           0x1f800003  //Write to clear irq flag
#define U0_CTL0_REG             0x1f800004  //Uart1/Lin(Local Interconnect Network) control register
#define U0_DATA_RDY_REG         0x1f800005  //Rx ready detect register
#define U0_LINBRK_REG           0x1f800006  //Write to send Lin break
#define U0_BRP_REG              0x1f800007  //Brp(Baud Rate Parallelization) setting register
/*Uart1 Registers*/
#define U1_READ_REG             0x1f800800  //RX data read register
#define U1_BUSY_REG             0x1f800801  //Tx busy detect register
#define U1_WRITE_REG            0x1f800802  //Tx data write register
#define U1_CLRIRQ_REG           0x1f800803  //Write to clear irq flag
#define U1_CTL0_REG             0x1f800804  //Uart1/Lin(Local Interconnect Network) control register
#define U1_DATA_RDY_REG         0x1f800805  //Rx ready detect register
#define U1_LINBRK_REG           0x1f800806  //Write to send Lin break
#define U1_BRP_REG              0x1f800807  //Brp(Baud Rate Parallelization) setting register
/*****************Register-Address Definition END**********************/

/**************************Uart 0 Functions****************************/
/*--------------------------------------------------------------------
 *Function Name:U0_Read
 *Last Modified:2017-05-15
 *Register Usage in Function:U0_DATA_RDY_REG, U0_READ_REG
 *Functional Description:
 *  Reading the Rx when data received is ready.
 *  Accepting no parameter.
 *--------------------------------------------------------------------*/
long U0_Read(){
  while(!MemoryRead32(U0_DATA_RDY_REG)){}      //checking if data is ready
  return MemoryRead32(U0_READ_REG);            //reading the data and set bit-8 0 to meet the standard of ASCII
}
/*--------------------------------------------------------------------
 *Function Name:U0_SendInt
 *Last Modified:2017-04-29
 *Register Usage in Function:U0_BUSY_REG, U0_WRITE_REG
 *Functional Description:
 *  Sending data through Uart0 Tx when Tx is not busy
 *  Accepting one parameter
 *  Parameters  | Value Description
 *  int c      | the int number expected to be sent out
 *--------------------------------------------------------------------*/
void U0_SendInt(int c){
  while(MemoryRead32(U0_BUSY_REG)){}  //checking if Tx is busy
  MemoryWrite32(U0_WRITE_REG,c);      //sending c out
}
/*--------------------------------------------------------------------
 *Function Name:U0_SendChar
 *Last Modified:2017-04-29
 *Register Usage in Function:U0_BUSY_REG, U0_WRITE_REG
 *Functional Description:
 *  Sending data through Uart0 Tx when Tx is not busy
 *  Accepting one parameter
 *  Parameters  | Value Description
 *  char c      | the char expected to be sent out
 *--------------------------------------------------------------------*/
void U0_SendChar(char c){
  while(MemoryRead32(U0_BUSY_REG)){}  //checking if Tx is busy
  MemoryWrite32(U0_WRITE_REG,c);      //sending c out
}
/*--------------------------------------------------------------------
 *Function Name:U0_SendString
 *Last Modified:2017-05-14
 *Register Usage in Function:U0_BUSY_REG, U0_WRITE_REG
 *Functional Description:
 *  Sending data through Uart0 Tx when Tx is not busy
 *  Accepting one parameter
 *  Parameters  | Value Description
 *  char* c     | the char expected to be sent out
 *--------------------------------------------------------------------*/
void U0_SendString(char* c){
  while(*c!='\0'){                      //checking if the string ends
    while(MemoryRead32(U0_BUSY_REG)){}  //checking if Tx is busy
    MemoryWrite32(U0_WRITE_REG,*c);     //sending a char out
    c++;                                //moving the pointer
  }
}
/*--------------------------------------------------------------------
 *Function Name:U0_LinMaster
 *Last Modified:2017-04-29
 *Register Usage in Function:U0_CTL0_REG, U0_LINBRK_REG, U0_WRITE_REG
 *Functional Description:
 *  Setting M2 Lin working in master mode
 *  Accepting one parameter
 *  Parameters     | Value Description
 *  int brklength  | 0=normal length,1=extreme length
 *--------------------------------------------------------------------*/
void U0_LinMaster(int brklength){
  MemoryWrite32(U0_CTL0_REG,brklength*32); //enable the LIN-Master
  MemoryWrite32(U0_LINBRK_REG,0x0);        //LIN sync BREAK pattern
  MemoryWrite32(U0_WRITE_REG,0x55);        //LIN sync pattern
}
/*--------------------------------------------------------------------
 *Function Name:U0_LinSlave
 *Last Modified:2017-04-29
 *Register Usage in Function:U0_CTL0_REG
 *Functional Description:
 *  Setting M2 Lin working in slave mode
 *  Accepting no parameter
 *--------------------------------------------------------------------*/
void U0_LinSlave(){
  MemoryWrite32(U0_CTL0_REG,0x8);   //enable the Lin-Slave
}
/**********************Uart 0 Functions END****************************/

/**************************Uart 1 Functions****************************/
/*--------------------------------------------------------------------
 *Function Name:U1_Read
 *Last Modified:2017-05-15
 *Register Usage in Function:U1_DATA_RDY_REG, U1_READ_REG
 *Functional Description:
 *  Reading the Rx when data received is ready.
 *  Accepting no parameter.
 *--------------------------------------------------------------------*/
long U1_Read(){
  while(!MemoryRead32(U1_DATA_RDY_REG)){}      //checking if data is ready
  return MemoryRead32(U1_READ_REG);            //reading the data and set bit-8 0 to meet the standard of ASCII
}
/*--------------------------------------------------------------------
 *Function Name:U1_SendInt
 *Last Modified:2017-04-29
 *Register Usage in Function:U1_BUSY_REG, U1_WRITE_REG
 *Functional Description:
 *  Sending data through Uart1 Tx when Tx is not busy
 *  Accepting one parameter
 *  Parameters  | Value Description
 *  int c       | the int number expected to be sent out
 *--------------------------------------------------------------------*/
void U1_SendInt(int c){
  while(MemoryRead32(U1_BUSY_REG)){}  //checking if Tx is busy
  MemoryWrite32(U1_WRITE_REG,c);      //sending c out
}
/*--------------------------------------------------------------------
 *Function Name:U1_SendChar
 *Last Modified:2017-04-29
 *Register Usage in Function:U1_BUSY_REG, U1_WRITE_REG
 *Functional Description:
 *  Sending data through Uart1 Tx when Tx is not busy
 *  Accepting one parameter
 *  Parameters  | Value Description
 *  char c      | the char expected to be sent out
 *--------------------------------------------------------------------*/
void U1_SendChar(char c){
  while(MemoryRead32(U1_BUSY_REG)){}  //checking if Tx is busy
  MemoryWrite32(U1_WRITE_REG,c);      //sending c out
}
/*--------------------------------------------------------------------
 *Function Name:U1_SendString
 *Last Modified:2017-05-14
 *Register Usage in Function:U1_BUSY_REG, U1_WRITE_REG
 *Functional Description:
 *  Sending data through Uart1 Tx when Tx is not busy
 *  Accepting one parameter
 *  Parameters  | Value Description
 *  char* c     | the string expected to be sent out
 *--------------------------------------------------------------------*/
void U1_SendString(char* c){
  while(*c!='\0'){                      //checking if the string ends
    while(MemoryRead32(U1_BUSY_REG)){}  //checking if Tx is busy
    MemoryWrite32(U1_WRITE_REG,*c);     //sending a char out
    c++;                                //moving the pointer
  }
}
/*--------------------------------------------------------------------
 *Function Name:U1_LinMaster
 *Last Modified:2017-04-29
 *Register Usage in Function:U1_CTL0_REG, U1_LINBRK_REG, U1_WRITE_REG
 *Functional Description:
 *  Setting M2 Lin working in master mode
 *  Accepting one parameter
 *  Parameters     | Value Description
 *  int brklength  | 0=normal length,1=extreme length
 *--------------------------------------------------------------------*/
void U1_LinMaster(int brklength){
  MemoryWrite32(U1_CTL0_REG,brklength*32); //enable the LIN-Master
  MemoryWrite32(U1_LINBRK_REG,0x0);        //LIN sync BREAK pattern
  MemoryWrite32(U1_WRITE_REG,0x55);        //LIN sync pattern
}
/*--------------------------------------------------------------------
 *Function Name:U1_LinSlave
 *Last Modified:2017-04-29
 *Register Usage in Function:U1_CTL0_REG
 *Functional Description:
 *  Setting M2 Lin working in slave mode
 *  Accepting no parameter
 *--------------------------------------------------------------------*/
void U1_LinSlave(){
  MemoryWrite32(U1_CTL0_REG,0x8);   //enable the Lin-Slave
}
/**********************Uart 1 Functions END****************************/
