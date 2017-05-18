#include "mcu.h"
#include "Module.h"

void getCommPC(char* comm){
    short i=0;
    while((comm[i++]=U0_Read())!='#'){}
    comm[i]='\0';
}

void user_interrupt(){
  char comm[100];
  getCommPC(comm);
  U0_SendString(comm);
  MemoryAnd(0x1f800804,0);
  MemoryWrite32(0x1f800803,1);
}

void main(){
  char outputTemp[5];
  char outputHumi[5];
  char comm[100];
  int dht11[5]={0};
  int i;
 
  while(1){
    DHT11(dht11);
    hexToDec(dht11[0],outputHumi);
    hexToDec(dht11[2],outputTemp);
    U0_SendString(outputHumi);
    U0_SendChar('+');
    U0_SendString(outputTemp);
    U0_SendChar('\n');
    U1_SendString("Humidity=");
    U1_SendString(outputHumi);
    U1_SendString("%\t");
    U1_SendString("Temperature=");
    U1_SendString(outputTemp);
    U1_SendString(" Degree Celsius\n");
    for(i=0;i<224000;i++){}
  }
}