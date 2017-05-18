#include "mcu.h"
#define SYS_IOCTL_REG   0x1f800704    //I/O control register 1=output 0=input
#define SYS_GPIO0_REG   0x1f800705    //I/O output register
#define SYS_GPIO1_REG   0x1f800706    //I/O input register
/*************************************************************/
/*This is user_interrupt*/
void user_interrupt(){}
/*************************************************************/
/*This is main function*/
void main(){
  int i;
  long a=0;
  MemoryWrite32(SYS_IOCTL_REG,0x1);   //I/O 0 output enabled
  while(1){
    MemoryWrite32(SYS_GPIO0_REG,0x1); //send out 1
    for(i=0;i<100;i++){
      a=(a<<1)+(MemoryRead32(SYS_GPIO1_REG))>>1;    //read I/O 1
    }
    MemoryWrite32(SYS_GPIO0_REG,0x0); //send out 0
    for(i=0;i<100;i++){
    }
  }
}
