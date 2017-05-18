#include "mcu.h"
#include "ASTRO.h"
void user_interrupt(){}
void main(){
  char i[3];
  int j;
  U1_SendString("+++");
  U0_SendChar(U1_Read());
  U1_SendChar('a');
  for(j=0;j<5;j++){
    i[j]=U1_Read();
  }
  puts("read\n");
  for(j=0;j<5;j++){
    U0_SendChar(i[j]);
  }
  U1_SendString("AT+WSSSID\n");
  for(j=0;j<20;j++){
    i[j]=U1_Read();
  }
  for(j=0;j<20;j++){
    U0_SendChar(i[j]);
  }
  U1_SendString("AT+ENTM\n");

  //for(j=0;j<50;j++){}
  //U0_SendChar(U1_Read());
}
