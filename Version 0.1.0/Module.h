#ifndef __Module_H__
#define __Module_H__

/*--------Uart 0 Functions--------*/
int U0_DataReady();
long U0_Read();
void U0_SendInt(int c);
void U0_SendChar(char c);
void U0_SendString(char* c);
void U0_LinMaster(int brklength);
void U0_LinSlave();

/*--------Uart 1 Functions--------*/
int U1_DataReady();
long U1_Read();
void U1_SendInt(int c);
void U1_SendChar(char c);
void U1_SendString(char* c);
void U1_LinMaster(int brklength);
void U1_LinSlave();

/*--------Interrupt Functions--------*/
void Sys_Irq(int enable);
void U0_DataIrq(int enable);
void U0_IrqClr();
void U1_DataIrq(int enable);
void U1_IrqClr();

/*--------Math Functions--------*/
int power(int a,int b);
void hexToDec(int hex,char* dec);

/*------------Module Functions------------*/
/*--DHT11 Humidity-Temperature Sensor--*/
void DHT11(int* result);
/*--WiFiLPT100--*/
void getRespond(char* respond);
short enterComm();
void exitComm();
void getUartF(char* UartF);
short setUartF(char* UartF);
void getUartFT(char* UartFT);
short setUartFT(char* UartFT);
void getUartFL(char* UartFL);
short setUartFL(char* UartFL);
void getUartTE(char* UartTE);
short setUartTE(char* UartTE);
void getSSID(char* SSID);
short setSSID(char* SSID);
void getWSKEY(char* WSKEY);
short setWSKEY(char* auth,char* encry,char* passwd);
void getLinkState(char* state);
void getSockANETP(char* NETP);
short setSockANETP(char* protocol,char* CS,char* port,char* ip);
void getSockATCPLK(char* TCPLK);

#endif