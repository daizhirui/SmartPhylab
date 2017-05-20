#include "mcu.h"
#define SYS_IOCTL_REG   0x1f800704    //I/O control register 1=output 0=input
#define SYS_GPIO0_REG   0x1f800705    //I/O output register
#define SYS_GPIO1_REG   0x1f800706    //I/O input register

void user_interrupt(){}
/*void main(){
  int a,i;
  MemoryWrite32(SYS_IOCTL_REG,0x0);
  while(1){
    a=MemoryRead32(SYS_GPIO1_REG)&0xffff-0xffce;
    puts(xtoa(a));
  }
}*/

void main(){
  int i,j;
  puts(xtoa(MemoryRead32(SYS_GPIO1_REG)));puts("\n");
  for(i=0;i<238100;i++){}
  MemoryOr32(SYS_IOCTL_REG,0x1);                //IOport output enable
  MemoryAnd32(SYS_GPIO0_REG,~(0x1));            //sending request
  for(i=0;i<4300;i++){}                             //maintaining request for 18ms
  //MemoryOr32(SYS_GPIO0_REG,0x1<<port);                //raising level
  for(i=0;i<16;i++){}                                //maintaining high level for 24us
  MemoryWrite32(SYS_IOCTL_REG,0x0);            //IOport input enable
  while(1){
    puts(xtoa(MemoryRead32(SYS_GPIO1_REG)));puts("\n");
  }
}
