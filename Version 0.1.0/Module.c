/**
* @file         Module.c  
* @brief        Functions for modules
* @author       ASTRO
* @date         2017-05-16 
* @version      0.1.0
* @copyright    ASTRO                                                              
***********************************************************/
#include "mcu.h"    //include headers
/**
 * @name        Address Definition
 * @{
 */
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

#define SYS_IOCTL_REG   0x1f800704    //I/O control register 1=output 0=input
#define SYS_GPIO0_REG   0x1f800705    //I/O output register
#define SYS_GPIO1_REG   0x1f800706    //I/O input register
#define SYS_IRQ_REG     0x1f800707    //System Irq register
/**@} *********************************************************/

/*--------------------Uart 0 Functions----------------------*/
/**
 * @name         U0_DataReady
 * @brief         This function returns the state of Rx of Uart0
 * @param[out]   state of Rx of Uart0
 * @return       0=not ready,1=ready
 ************************************************************/
int U0_DataReady(){
  return MemoryRead32(U0_DATA_RDY_REG);
}
/**
 * @name         U0_Read
 * @brief         This function returns the data received via Uart0
 * @param[out]   data from Uart0
 * @return       data from Uart0
 ************************************************************/
long U0_Read(){
  while(!MemoryRead32(U0_DATA_RDY_REG)){}      //checking if data is ready
  return MemoryRead32(U0_READ_REG);            //reading the data and set bit-8 0 to meet the standard of ASCII
}
/**
 * @name      U0_SendInt
 * @brief      This function is used to send out int data
 * @param[in]   c   int data to send out
 * @return    void
 ************************************************************/ 
void U0_SendInt(int c){
  while(MemoryRead32(U0_BUSY_REG)){}  //checking if Tx is busy
  MemoryWrite32(U0_WRITE_REG,c);      //sending c out
}
/**
 * @name      U0_SendChar
 * @brief      This function is used to send out char data
 * @param[in]   c   char data to send out
 * @return    void
 ************************************************************/ 
void U0_SendChar(char c){
  while(MemoryRead32(U0_BUSY_REG)){}  //checking if Tx is busy
  MemoryWrite32(U0_WRITE_REG,c);      //sending c out
}
/**
 * @name      U0_SendString
 * @brief      This function is used to send out a string
 * @param[in]   c   a pointer points to the string
 * @return    void
 ************************************************************/ 
void U0_SendString(char* c){
  while(*c!='\0'){                      //checking if the string ends
    while(MemoryRead32(U0_BUSY_REG)){}  //checking if Tx is busy
    MemoryWrite32(U0_WRITE_REG,*c);     //sending a char out
    c++;                                //moving the pointer
  }
}
/**
 * @name      U0_LinMaster
 * @brief      This function is for setting M2 Lin working in master mode
 * @param[in] brklength the length of the break signal,0=normal length,1=extreme length
 * @return    void
 ************************************************************/ 
void U0_LinMaster(int brklength){
  MemoryWrite32(U0_CTL0_REG,brklength*32); //enable the LIN-Master
  MemoryWrite32(U0_LINBRK_REG,0x0);        //LIN sync BREAK pattern
  MemoryWrite32(U0_WRITE_REG,0x55);        //LIN sync pattern
}
/**
 * @name      U0_LinSlave
 * @brief      This function is for setting M2 Lin working in slave mode
 * @return    void
 ************************************************************/ 
void U0_LinSlave(){
  MemoryWrite32(U0_CTL0_REG,0x8);   //enable the Lin-Slave
}
/*----------------Uart 0 Functions END----------------------*/

/*--------------------Uart 1 Functions----------------------*/
/**
 * @name         U1_DataReady
 * @brief         This function returns the state of Rx of Uart0
 * @param[out]   state of Rx of Uart1
 * @return       0=not ready,1=ready
 ************************************************************/
int U1_DataReady(){
  return MemoryRead32(U1_DATA_RDY_REG);
}
/**
 * @name         U1_Read
 * @brief         This function returns the data received via Uart0
 * @param[out]   data from Uart1
 * @return       data from Uart1
 ************************************************************/
long U1_Read(){
  while(!MemoryRead32(U1_DATA_RDY_REG)){}      //checking if data is ready
  return MemoryRead32(U1_READ_REG);            //reading the data and set bit-8 0 to meet the standard of ASCII
}
/**
 * @name      U1_SendInt
 * @brief      This function is used to send out int data
 * @param[in]   c   int data to send out
 * @return    void
 ************************************************************/ 
void U1_SendInt(int c){
  while(MemoryRead32(U1_BUSY_REG)){}  //checking if Tx is busy
  MemoryWrite32(U1_WRITE_REG,c);      //sending c out
}
/**
 * @name      U1_SendChar
 * @brief      This function is used to send out char data
 * @param[in]   c   char data to send out
 * @return    void
 ************************************************************/ 
void U1_SendChar(char c){
  while(MemoryRead32(U1_BUSY_REG)){}  //checking if Tx is busy
  MemoryWrite32(U1_WRITE_REG,c);      //sending c out
}
/**
 * @name      U1_SendString
 * @brief      This function is used to send out a string
 * @param[in]   c   a pointer points to the string
 * @return    void
 ************************************************************/ 
void U1_SendString(char* c){
  while(*c!='\0'){                      //checking if the string ends
    while(MemoryRead32(U1_BUSY_REG)){}  //checking if Tx is busy
    MemoryWrite32(U1_WRITE_REG,*c);     //sending a char out
    c++;                                //moving the pointer
  }
}
/**
 * @name      U1_LinMaster
 * @brief      This function is for setting M2 Lin working in master mode
 * @param[in] brklength the length of the break signal,0=normal length,1=extreme length
 * @return    void
 ************************************************************/ 
void U1_LinMaster(int brklength){
  MemoryWrite32(U1_CTL0_REG,brklength*32); //enable the LIN-Master
  MemoryWrite32(U1_LINBRK_REG,0x0);        //LIN sync BREAK pattern
  MemoryWrite32(U1_WRITE_REG,0x55);        //LIN sync pattern
}
/**
 * @name      U0_LinSlave
 * @brief      This function is for setting M2 Lin working in slave mode
 * @return    void
 ************************************************************/ 
void U1_LinSlave(){
  MemoryWrite32(U1_CTL0_REG,0x8);   //enable the Lin-Slave
}
/*----------------Uart 1 Functions END----------------------*/

/*-------------------Interrupt Functions--------------------*/
/**
 * @name        Sys_Irq
 * @brief        This function is used to enable or unable the system Irq.
 * @param[in]   enable  the value of the switch
 * @return      void
 ************************************************************/ 
void Sys_Irq(int enable){
  MemoryAnd32(SYS_CTL0_REG,!(0x1));   //turn off Irq anyway
  MemoryOr32(SYS_CTL0_REG,enable);    //1=enable,0=unable Irq
}
/**
 * @name        U0_DataIrq
 * @brief        This function is used to enable or unable the Uart0 data ready Irq.
 * @param[in]   enable  the value of the switch
 * @return      void
 ************************************************************/ 
void U0_DataIrq(int enable){
  MemoryAnd32(U0_CTL0_REG,~(0x1));  //turn off Irq anyway
  MemoryOr32(U0_CTL0_REG,enable);   //1=enable,0=unable Irq
  MemoryOr32(SYS_CTL0_REG,0x1);     //enable system Irq
}
/**
 * @name        U0_IrqClr
 * @brief        This function is used to clear the Irq flag of Uart0
 * @return      void
 ************************************************************/ 
void U0_IrqClr(){
  MemoryWrite32(U0_CLRIRQ_REG,0x1);
}
/**
 * @name        U1_DataIrq
 * @brief        This function is used to enable or unable the Uart1 data ready Irq.
 * @param[in]   enable  the value of the switch
 * @return      void
 ************************************************************/ 
void U1_DataIrq(int enable){
  MemoryAnd32(U1_CTL0_REG,~(0x1));  //turn off Irq anyway
  MemoryOr32(U1_CTL0_REG,enable);   //1=enable,0=unable Irq
  MemoryOr32(SYS_CTL0_REG,0x1);     //enable system Irq
}
/**
 * @name        U1_IrqClr
 * @brief        This function is used to clear the Irq flag of Uart1
 * @return      void
 ************************************************************/ 
void U1_IrqClr(){
  MemoryWrite32(U1_CLRIRQ_REG,0x1);     //write any value to U1_CLRIRQ_REG to clear Irq
}
/*-------------------Interrupt Functions--------------------*/

/*---------------------Math Functions-----------------------*/
/**
 * @name        power
 * @brief        The function is for calculating a^b.
 * @param[in]   a  a of a^b
 * @param[in]   b  b of a^b
 * @param[out]  a
 * @return      the result of a^b
 ************************************************************/ 
int power(int a,int b){
  int i;
  if(b==0){return 1;}       //check if the index b is 0
  if(b==1){return a;}       //check if the index b is 1
  for(i=0;i<b;i++){a*=a;}   //other cases
  return a;
}
/**
 * @name        hexToDec
 * @brief       This function is used for converting hex style number into dec style string.
 * @param[in]   hex   the source number
 * @param[in]   dec   the pointer points to the result array
 * @return      decimal style string
 * @note        This function is not recommended to use in released version.
 ************************************************************/ 
void hexToDec(int hex,char* dec){
  short i,j,size=0;
  int opt;
  if(hex<0){                                    //check if input value is < 0
      hex=-hex;
      dec[i]='-';
      size=1;
  }
  if(hex==0){dec[0]='0';dec[1]='\0';return;}    //check if input value is 0
  int temp=hex;
  for(i=0;temp;i++){                            //calculating the length of hex
    temp/=10;
  }
  temp=hex;
  for(j=size;j<i;j++){                          //converting to dec style
    opt=power(10,i-j-1);
    dec[j]=temp/opt+48;
    temp-=temp/opt*opt;
  }
  dec[i]='\0';                                  //add the end symbol
}
/*-----------------Math Functions END-----------------------*/

/*--------------------Module Functions----------------------*/
/*DHT11 Humidity-Temperature Sensor, IO0*/
/**
 * @name        DHT11
 * @brief       This function is for DHT11 humidity-temperature sensor.
 *              The function drives DHT11 sensor via IO0 and stores the result.
 * @param[in]   a pointer points to an int result array
 * @return      void
 ************************************************************/ 
void DHT11(int* result){
  int data[41];
  long level0;
  int i,j;
  for(i=0;i<5;i++){
      result[i]=0;                                        //initialing the result array
  }
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
  for(i=0;i<40;i+=8){
    for(j=i;j<i+8;j++){
      if(data[j]<5){
        result[i/8]=result[i/8]<<1;
      }else{
        result[i/8]=(result[i/8]<<1)+1;
      }
    }
  }
}

/**
 * @name WiFiLPT100 Uart1
 * @brief The basic procedure is sending the AT command -> getting the repeat of the command
 *         -> getting the result of the command -> checking the result
 */
/**
 * @name        getRespond
 * @brief       This function is used to get responce from WiFiLPT100.
 * @param[in]   respond
 * @return      data from WiFiLPT100 module via Uart1
 ************************************************************/ 
void getRespond(char* respond){
    short i=0;
    while((respond[i++]=U1_Read())!=0xd){}  //get the responce, stop once get 0xd
}
/**
 * @name        enterComm
 * @brief       This function is used to set WiFiLPT100 enter Command mode.
 * @param[out]  operation result
 * @return      0=failure, 1=success
 ************************************************************/ 
short enterComm(){
    char respond[3]={0};
    short i=0;
    U1_SendString("+++");       //send the command of entering command mode
    U1_Read();                  //get the responce
    U1_SendChar('a');           //return the responce
    getRespond(respond);        //get the responce
    if(respond[0]=='+'&&respond[1]=='o'&&respond[2]=='k'){  //check if WiFiLPT100 has entered command mode
        return 1;
    }else{
        return 0;
    }
}
/**
 * @name        exitComm
 * @brief        This function is used to set WiFiLPT100 exit Command mode.
 * @return      void
 ************************************************************/ 
void exitComm(){
    U1_SendString("AT+ENTM\n");     //send the command of exiting command mode
}
/**
 * @name        getUartF
 * @brief       This function is for WiFiLPT100.
 *              This function is used to get the preference of Uart Frame Mode enable
 * @param[in]   UartF   a pointer points to the result array
 * @param[out]  the present preference
 * @return      void
 ************************************************************/ 
void getUartF(char* UartF){
    char respond[10]={0};
    short i=0;
    U1_SendString("AT+UARTF\n");    //send the command
    getRespond(respond);            //get the repeat of the command
    getRespond(respond);            //get the result of the command
    while(respond[i+4]!=0xd){       //storing the result into UartF
        UartF[i]=respond[i+4];
        i++;
    }
    UartF[i]='\0';
}
/**
 * @name        setUartF
 * @brief       This function is for WiFiLPT100.
 *              This function is used to setup the preference of Uart Frame Mode enable
 * @param[in]   UartF   a pointer points to the parameter array
 * @param[out]  operation result
 * @return      0=failure,1=success
 ************************************************************/ 
short setUartF(char* UartF){
    char respond[20]={0};
    short i=0;
    U1_SendString("AT+UARTF=");     //send the command header
    U1_SendString(UartF);           //send the parameter
    U1_SendChar('\n');              //send the end symbol of the command
    getRespond(respond);            //get the repeat of the command
    getRespond(respond);            //get the result of the command
    if(respond[0]=='+'&&respond[1]=='o'&&respond[2]=='k'){  //checking the result
        return 1;
    }else{
        return 0;
    }
}
/**
 * @name        getUartFT
 * @brief       This function is for WiFiLPT100.
 *              This function is used to get the preference of time between 2 Uart Frames.
 * @param[in]   UartFT   a pointer points to the result array
 * @param[out]  the present preference
 * @return      void
 ************************************************************/ 
void getUartFT(char* UartFT){
    char respond[10]={0};
    short i=0;
    U1_SendString("AT+UARTFT\n");   //send the command
    getRespond(respond);            //get the repeat of the command
    getRespond(respond);            //get the result of the command
    while(respond[i+4]!=0xd){       //storing the result into UartFT
        UartFT[i]=respond[i+4];
        i++;
    }
    UartFT[i]='\0';
}
/**
 * @name        setUartFT
 * @brief       This function is for WiFiLPT100.
 *              This function is used to setup the preference of time between 2 Uart Frames.
 * @param[in]   UartFT   a pointer points to the parameter array
 * @param[out]  operation result
 * @return      0=failure,1=success
 ************************************************************/ 
short setUartFT(char* UartFT){
    char respond[20]={0};
    short i=0;
    U1_SendString("AT+UARTFT=");    //send the command header
    U1_SendString(UartFT);          //send the parameter
    U1_SendChar('\n');              //send the end symbol of the command
    getRespond(respond);            //get the repeat of the command
    getRespond(respond);            //get the result of the command
    if(respond[0]=='+'&&respond[1]=='o'&&respond[2]=='k'){  //checking the result
        return 1;
    }else{
        return 0;
    }
}
/**
 * @name        getUartFL
 * @brief       This function is for WiFiLPT100.
 *              This function is used to get the preference of Uart Frame length.
 * @param[in]   UartFL   a pointer points to the result array
 * @param[out]  the present preference
 * @return      void
 ************************************************************/ 
void getUartFL(char* UartFL){
    char respond[10]={0};
    short i=0;
    U1_SendString("AT+UARTFL\n");       //send the command
    getRespond(respond);                //get the repeat of the command
    getRespond(respond);                //get the result of the command
    while(respond[i+4]!=0xd){           //storing the result into UartFL
        UartFL[i]=respond[i+4];
        i++;
    }
    UartFL[i]='\0';
}
/**
 * @name        setUartFL
 * @brief       This function is for WiFiLPT100.
 *              This function is used to set the preference of Uart Frame length.
 * @param[in]   UartFL   a pointer points to the parameter array
 * @param[out]  operation result
 * @return      0=failure,1=success
 ************************************************************/ 
short setUartFL(char* UartFL){
    char respond[20]={0};
    short i=0;
    U1_SendString("AT+UARTFL=");    //send the command header
    U1_SendString(UartFL);          //send the parameter
    U1_SendChar('\n');              //send the end symbol of the command
    getRespond(respond);            //get the repeat of the command
    getRespond(respond);            //get the result of the command
    if(respond[0]=='+'&&respond[1]=='o'&&respond[2]=='k'){      //check the result
        return 1;
    }else{
        return 0;
    }
}
/**
 * @name        getUartTE
 * @brief       This function is for WiFiLPT100.
 *              This function is used to get the preference of Uart FreeFrame Mode.
 * @param[in]   UartTE   a pointer points to the result array
 * @param[out]  the present preference
 * @return      void
 ************************************************************/ 
void getUartTE(char* UartTE){
    char respond[10]={0};
    short i=0;
    U1_SendString("AT+UARTTE\n");       //send the command header
    getRespond(respond);                //get the repeat of the command
    getRespond(respond);                //get the result of the command
    while(respond[i+4]!=0xd){           //storing the result into UartTE
        UartTE[i]=respond[i+4];
        i++;
    }
    UartTE[i]='\0';
}
/**
 * @name        setUartTE
 * @brief       This function is for WiFiLPT100.
 *              This function is used to set the preference of Uart FreeFrame Mode.
 * @param[in]   UartTE   a pointer points to the parameter array
 * @param[out]  operation result
 * @return      0=failure,1=success
 ************************************************************/ 
short setUartTE(char* UartTE){
    char respond[20]={0};
    short i=0;
    U1_SendString("AT+UARTTE=");        //send the command header
    U1_SendString(UartTE);              //send the parameter
    U1_SendChar('\n');                  //send the end symbol of the command
    getRespond(respond);                //get the repeat of the command
    getRespond(respond);                //get the result of the command
    if(respond[0]=='+'&&respond[1]=='o'&&respond[2]=='k'){  //check the result
        return 1;
    }else{
        return 0;
    }
}
/**
 * @name        getSSID
 * @brief       This function is for WiFiLPT100.
 *              This function is used to get the preference of target AP's SSID.
 * @param[in]   SSID   a pointer points to the result array
 * @param[out]  the present preference
 * @return      void
 ************************************************************/ 
void getSSID(char* SSID){
    char respond[30]={0};
    short i=0;
    U1_SendString("AT+WSSSID\n");   //send the command
    getRespond(respond);            //get the feedback "AT+WSSSID"
    getRespond(respond);            //get the SSID
    while(respond[i+4]!=0xd){       //storing the result into SSID
        SSID[i]=respond[i+4];
        i++;
    }
    SSID[i]='\0';
}
/**
 * @name        setSSID
 * @brief       This function is for WiFiLPT100.
 *              This function is used to set the preference of target AP's SSID.
 * @param[in]   SSID   a pointer points to the parameter array
 * @param[out]  operation result
 * @return      0=failure,1=success
 ************************************************************/ 
short setSSID(char* SSID){
    char respond[3]={0};
    char para[20]={0};
    short i=0;
    U1_SendString("AT+WSSSID=");       //send the command header
    U1_SendString(SSID);               //send the parameter
    U1_SendChar('\n');                 //send the end symbol of the command
    getRespond(respond);               //get the repeat of the command
    getRespond(respond);               //get the result of the command
    if(respond[0]=='+'&&respond[1]=='o'&&respond[2]=='k'){  //check the result
        return 1;
    }else{
        return 0;
    }
}
/**
 * @name        getWSKEY
 * @brief       This function is for WiFiLPT100.
 *              This function is used to get the preference of target AP's Key.
 * @param[in]   WSKEY   a pointer points to the result array
 * @param[out]  the present preference
 * @return      void
 ************************************************************/ 
void getWSKEY(char* WSKEY){
    char respond[40]={0};
    short i=0;
    U1_SendString("AT+WSKEY\n");        //send the command
    getRespond(respond);                //get the repeat of the command
    getRespond(respond);                //get the result of the command
    while(respond[i+4]!=0xd){           //storing the result into WSKEY
        WSKEY[i]=respond[i+4];
        i++;
    }
    WSKEY[i]='\0';
}
/**
 * @name        setWSKEY
 * @brief       This function is for WiFiLPT100.
 *              This function is used to set the preference of target AP's Key.
 * @param[in]   auth   authorization method
 * @param[in]   encry   encry method
 * @param[in]   passwd  password
 * @param[out]  operation result
 * @return      0=failure,1=success
 ************************************************************/ 
short setWSKEY(char* auth,char* encry,char* passwd){
    char respond[40]={0};
    short i;
    U1_SendString("AT+WSKEY=");     //send the command header
    U1_SendString(auth);            //send the parameter--authorization method
    U1_SendChar(',');
    U1_SendString(encry);           //send the parameter--encry method
    U1_SendChar(',');
    U1_SendString(passwd);          //send the parameter--password of target AP
    U1_SendChar('\n');
    getRespond(respond);            //get the repeat of the command
    getRespond(respond);            //get the result of the command
    if(respond[0]=='+'&&respond[1]=='o'&&respond[2]=='k'){
        return 1;
    }else{
        return 0;
    }
}
/**
 * @name        getLinkState
 * @brief       This function is for WiFiLPT100.
 *              This function is used to get the state of WiFi connection
 * @param[in]   state   a pointer points to the result array
 * @param[out]  the present preference
 * @return      void
 ************************************************************/ 
void getLinkState(char* state){
    char respond[50]={0};
    short i=0;
    U1_SendString("AT+WSLK\n");     //send the command
    getRespond(respond);            //get the repeat of the command
    getRespond(respond);            //get the result of the command
    while(respond[i+4]!=0xd){       //storing the result into state
        state[i]=respond[i+4];
        i++;
    }
    state[i]='\0';
}
/**
 * @name        getSockANETP
 * @brief       This function is for WiFiLPT100.
 *              This function is used to get the preference of Sock A.
 * @param[in]   NETP   a pointer points to the result array
 * @param[out]  the present preference
 * @return      void
 ************************************************************/ 
void getSockANETP(char* NETP){
    char respond[30]={0};
    short i=0;
    U1_SendString("AT+NETP\n");     //send the command
    getRespond(respond);            //get the repeat of the command
    getRespond(respond);            //get the result of the command
    while(respond[i+4]!=0xd){       //storing the result into NETP
        NETP[i]=respond[i+4];
        i++;
    }
    NETP[i]='\0';
}
/**
 * @name        setSockANETP
 * @brief       This function is for WiFiLPT100.
 *              This function is used to set the preference of Sock A.
 * @param[in]   protocol   TCP or UDP
 * @param[in]   CS      SERVER or CLIENT
 * @param[in]   port    the port to communicate
 * @param[in]   ip      the IP address of target server
 * @param[out]  operation result
 * @return      0=failure,1=success
 ************************************************************/ 
short setSockANETP(char* protocol,char* CS,char* port,char* ip){
    char respond[50]={0};
    U1_SendString("AT+NETP=");      //send the command header
    U1_SendString(protocol);        //send the parameter--protocol 
    U1_SendChar(',');
    U1_SendString(CS);              //send the parameter--CS
    U1_SendChar(',');
    U1_SendString(port);            //send the parameter--port
    U1_SendChar(',');
    U1_SendString(ip);              //send the parameter--ip
    U1_SendChar('\n');
    getRespond(respond);            //get the repeat of the command
    getRespond(respond);            //get the result of the command
    if(respond[0]=='+'&&respond[1]=='o'&&respond[2]=='k'){  //check the result
        return 1;
    }else{
        return 0;
    }
}
/**
 * @name        getSockANETP
 * @brief       This function is for WiFiLPT100.
 *              This function is used to get the state of Sock A TCP.
 * @param[in]   NETP   a pointer points to the result array
 * @param[out]  the present preference
 * @return      void
 ************************************************************/ 
void getSockATCPLK(char* TCPLK){
    char respond[10]={0};
    short i=0;
    U1_SendString("AT+TCPLK\n");    //send the command
    getRespond(respond);            //get the repeat of the command
    getRespond(respond);            //get the result of the command
    while(respond[i+4]!=0xd){       //storing the result into TCPLK
        TCPLK[i]=respond[i+4];
        i++;
    }
    TCPLK[i]='\0';
}
/*-------------------Module Functions END-------------------*/
