/*----------------------------------------------------------------------
 * TITLE: Communication Module Between M2 and DHT11-Sensor
 * AUTHOR: DaiZhirui
 * DATE CREATED: 2017-05-02
 * FILENAME: GPIO-DHT11.c
 * PROJECT: M2 Laboratory
 * COPYRIGHT: DaiZhirui
 * DESCRIPTION:
 *    The communication module between M2 and DHT11-Sensor, based on GPIO
 * MODIFICATION HISTORY:
 *  2017-05-02: added user_interrupt,DHT11,main
 *---------------------------------------------------------------------*/
#include "mcu.h"
/*********************Register-Address Definition**********************/
#define SYS_IOCTL_REG   0x1f800704    //I/O control register 1=output 0=input
#define SYS_GPIO0_REG   0x1f800705    //I/O output register
#define SYS_GPIO1_REG   0x1f800706    //I/O input register
/*****************Register-Address Definition END**********************/
/*--------------------------------------------------------------------
 *Function Name:user_interrupt
 *Last Modified:2017-05-02
 *--------------------------------------------------------------------*/
void user_interrupt(){}
/*--------------------------------------------------------------------
 *Function Name:DHT11
 *Last Modified:2017-05-02
 *Register Usage in Function:SYS_IOCTL_REG,SYS_GPIO0_REG,SYS_GPIO1_REG
 *Functional Description:
 *  Setup the IOport for input or output
 *  Accepting 2 Parameters
 *  Parameters  | Value Description
 *  int port    | port=0-15 mapping IOport0-15
 *  int io      | 1=output 0=input
 *Notes:
 *  each for-loop costs 4.28 us
 *--------------------------------------------------------------------*/
void DHT11(){
  int data[41];
  int result[5];
  long level0;
  int i,j;
  for(i=0;i<238100;i++){}                                 //waiting for 1s to skip the unstable state of DHT11-Sensor
  MemoryOr32(SYS_IOCTL_REG,0x1);                          //IOport output enable
  MemoryAnd32(SYS_GPIO0_REG,~(0x1));                      //sending request
  level0=MemoryRead32(SYS_GPIO1_REG);                     //getting the value of level0
  for(i=0;i<4300;i++){}                                   //maintaining request for 18ms
  MemoryOr32(SYS_GPIO0_REG,0x1);                          //raising level
  for(i=0;i<8;i++){}                                      //maintaining high level for 37.6us
  MemoryWrite32(SYS_IOCTL_REG,0x0);                       //IOport input enable
  while(!(MemoryRead32(SYS_GPIO1_REG)-level0)){}          //detecting responding signal
  while(MemoryRead32(SYS_GPIO1_REG)-level0){}             //detecting level raised by DHT11
  for(i=0;i<40;i++){
    j=0;                                                  //reset the counter
    while(!(MemoryRead32(SYS_GPIO1_REG)-level0)){j++;}    //detecting bit starting signal
    j=0;                                                  //reset the counter
    while(MemoryRead32(SYS_GPIO1_REG)-level0){j++;}       //detecting bit length
    data[i]=j;                                            //storing the data
  }
  j=0;
  while(!(MemoryRead32(SYS_GPIO1_REG)-level0)){j++;}      //measuring ending signal length
  data[40]=j;                                             //storing the data
  for(i=0;i<41;i++){
    puts(xtoa(data[i]));                                  //print out the data set
    puts("\n");
  }
  for(i=0;i<5;i++){
    result[i]=0;
  }
  for(i=0;i<40;i+=8){
    for(j=i;j<i+8;j++){
      if(data[j]<5){
        result[i/8]=result[i/8]<<1;
      }else{
        result[i/8]=(result[i/8]<<1)+1;
      }
    }
  }
  puts("result:\n");
  for(i=0;i<5;i++){
    puts(xtoa(result[i]));
    puts("\n");
  }
}
void main(){
  DHT11();
}
