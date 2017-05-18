#ifndef __WiFiLPT100_H__
#define __WiFiLPT100_H__

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
void getLinkState(char* state;
void getSockANETP(char* NETP);
short setSockANETP(char* protocol,char* CS,char* port,char* ip);
void getSockATCPLK(char* TCPLK);

#endif