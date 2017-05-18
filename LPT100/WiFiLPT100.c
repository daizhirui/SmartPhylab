#include "mcu.h"
#include "ASTRO.h"

void getRespond(char* respond){
    short i=0;
    while((respond[i++]=U1_Read())!=0xd){}
}
short enterComm(){
    char respond[3]={0};
    short i=0;
    U1_SendString("+++");
    U1_Read();
    U1_SendChar('a');
    getRespond(respond);
    if(respond[0]=='+'&&respond[1]=='o'&&respond[2]=='k'){
        return 1;
    }else{
        return 0;
    }
}
void exitComm(){
    U1_SendString("AT+ENTM\n");
}
void getUartF(char* UartF){
    char respond[10]={0};
    short i=0;
    U1_SendString("AT+UARTF\n");
    getRespond(respond);
    getRespond(respond);
    while(respond[i+4]!=0xd){
        UartF[i]=respond[i+4];
        i++;
    }
    UartF[i]='\0';
}
short setUartF(char* UartF){
    char respond[20]={0};
    short i=0;
    U1_SendString("AT+UARTF=");
    U1_SendString(UartF);
    U1_SendChar('\n');
    getRespond(respond);
    getRespond(respond);
    if(respond[0]=='+'&&respond[1]=='o'&&respond[2]=='k'){
        return 1;
    }else{
        return 0;
    }
}
void getUartFT(char* UartFT){
    char respond[10]={0};
    short i=0;
    U1_SendString("AT+UARTFT\n");
    getRespond(respond);
    getRespond(respond);
    while(respond[i+4]!=0xd){
        UartFT[i]=respond[i+4];
        i++;
    }
    UartFT[i]='\0';
}
short setUartFT(char* UartFT){
    char respond[20]={0};
    short i=0;
    U1_SendString("AT+UARTFT=");
    U1_SendString(UartFT);
    U1_SendChar('\n');
    getRespond(respond);
    getRespond(respond);
    if(respond[0]=='+'&&respond[1]=='o'&&respond[2]=='k'){
        return 1;
    }else{
        return 0;
    }
}
void getUartFL(char* UartFL){
    char respond[10]={0};
    short i=0;
    U1_SendString("AT+UARTFL\n");
    getRespond(respond);
    getRespond(respond);
    while(respond[i+4]!=0xd){
        UartFL[i]=respond[i+4];
        i++;
    }
    UartFL[i]='\0';
}
short setUartFL(char* UartFL){
    char respond[20]={0};
    short i=0;
    U1_SendString("AT+UARTFL=");
    U1_SendString(UartFL);
    U1_SendChar('\n');
    getRespond(respond);
    getRespond(respond);
    if(respond[0]=='+'&&respond[1]=='o'&&respond[2]=='k'){
        return 1;
    }else{
        return 0;
    }
}
void getUartTE(char* UartTE){
    char respond[10]={0};
    short i=0;
    U1_SendString("AT+UARTTE\n");
    getRespond(respond);
    getRespond(respond);
    while(respond[i+4]!=0xd){
        UartTE[i]=respond[i+4];
        i++;
    }
    UartTE[i]='\0';
}
short setUartTE(char* UartTE){
    char respond[20]={0};
    short i=0;
    U1_SendString("AT+UARTTE=");
    U1_SendString(UartTE);
    U1_SendChar('\n');
    getRespond(respond);
    getRespond(respond);
    if(respond[0]=='+'&&respond[1]=='o'&&respond[2]=='k'){
        return 1;
    }else{
        return 0;
    }
}
void getSSID(char* SSID){
    char respond[30]={0};
    short i=0;
    U1_SendString("AT+WSSSID\n");
    getRespond(respond);            //get the feedback "AT+WSSSID"
    getRespond(respond);            //get the SSID
    while(respond[i+4]!=0xd){
        SSID[i]=respond[i+4];
        i++;
    }
    SSID[i]='\0';
}
short setSSID(char* SSID){
    char respond[3]={0};
    char para[20]={0};
    short i=0;
    for(;SSID[i]!='\0';i++){
        para[i]=SSID[i];
    }
    para[i]='\0';
    U1_SendString("AT+WSSSID=");
    U1_SendString(para);
    U1_SendChar('\n');
    getRespond(respond);
    getRespond(respond);
    if(respond[0]=='+'&&respond[1]=='o'&&respond[2]=='k'){
        return 1;
    }else{
        return 0;
    }
}
void getWSKEY(char* WSKEY){
    char respond[40]={0};
    short i=0;
    U1_SendString("AT+WSKEY\n");
    getRespond(respond);
    getRespond(respond);
    while(respond[i+4]!=0xd){
        WSKEY[i]=respond[i+4];
        i++;
    }
    WSKEY[i]='\0';
}
short setWSKEY(char* auth,char* encry,char* passwd){
    char respond[40]={0};
    short i;
    U1_SendString("AT+WSKEY=");
    U1_SendString(auth);
    U1_SendChar(',');
    U1_SendString(encry);
    U1_SendChar(',');
    U1_SendString(passwd);
    U1_SendChar('\n');
    getRespond(respond);
    getRespond(respond);
    if(respond[0]=='+'&&respond[1]=='o'&&respond[2]=='k'){
        return 1;
    }else{
        return 0;
    }
}
void getLinkState(char* state){
    char respond[50]={0};
    short i=0;
    U1_SendString("AT+WSLK\n");
    getRespond(respond);
    getRespond(respond);
    while(respond[i+4]!=0xd){
        state[i]=respond[i+4];
        i++;
    }
    state[i]='\0';
}
void getSockANETP(char* NETP){
    char respond[30]={0};
    short i=0;
    U1_SendString("AT+NETP\n");
    getRespond(respond);
    getRespond(respond);
    while(respond[i+4]!=0xd){
        NETP[i]=respond[i+4];
        i++;
    }
    NETP[i]='\0';
}
short setSockANETP(char* protocol,char* CS,char* port,char* ip){
    char respond[50]={0};
    U1_SendString("AT+NETP=");
    U1_SendString(protocol);
    U1_SendChar(',');
    U1_SendString(CS);
    U1_SendChar(',');
    U1_SendString(port);
    U1_SendChar(',');
    U1_SendString(ip);
    U1_SendChar('\n');
    getRespond(respond);
    getRespond(respond);
    if(respond[0]=='+'&&respond[1]=='o'&&respond[2]=='k'){
        return 1;
    }else{
        return 0;
    }
}
void getSockATCPLK(char* TCPLK){
    char respond[10]={0};
    short i=0;
    U1_SendString("AT+TCPLK\n");
    getRespond(respond);
    getRespond(respond);
    while(respond[i+4]!=0xd){
        TCPLK[i]=respond[i+4];
        i++;
    }
    TCPLK[i]='\0';
}