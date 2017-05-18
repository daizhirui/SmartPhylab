/**
* @file         phylab.c  
* @brief        main program of M2 Lab
* @author       ASTRO
* @date         2017-05-16 
* @version      0.1.0 
* @copyright    ASTRO                                                              
***********************************************************/
#include "mcu.h"
#include "Module.h"
/**
 * @name  getCommPC
 * @brief This function is used to get the command from PC
 * @param[in] comm a pointer points to the result array
 * @return void
 ************************************************************/ 
void getCommPC(char* comm){
    short i=0;
    while((comm[i++]=U0_Read())!='#'){}
    comm[i]='\0';
}
/**
 * @name  setWiFiSTA
 * @brief This function is used to setup the STA of WiFiLPT100 module
 * @param[in] comm a pointer points to the command received from PC
 * @return void
 ************************************************************/ 
void setWiFiSTA(char* comm){
  char ssid[20]={'0'};
  char auth[8]={'0'};
  char encry[6]={'0'};
  char passwd[17]={'0'};
  short i=0,j=0;
  while(comm[i++]!='+'){}
  for(j=0,i;comm[i]!='+';j++,i++){
    ssid[j]=comm[i];
  }
  ssid[j]='\0';
  for(j=0,i++;comm[i]!='+';j++,i++){
    auth[j]=comm[i];
  }
  auth[j]='\0';
  for(j=0,i++;comm[i]!='+';j++,i++){
    encry[j]=comm[i];
  }
  encry[j]='\0';
  for(j=0,i++;comm[i]!='+';j++,i++){
    passwd[j]=comm[i];
  }
  passwd[j]='\0';
  setSSID(ssid);
  setWSKEY(auth,encry,passwd);
}
/**
 * @name  setWiFiTCP
 * @brief This function is used to setup the TCP of WiFiLPT100 module
 * @param[in] comm a pointer points to the command received from PC
 * @return void
 ************************************************************/ 
void setWiFiTCP(char* comm){
  char protocol[4]={0};
  char CS[7]={0};
  char port[6]={0};
  char IP[16]={0};
  short i=0,j=0;
  while(comm[i++]!='+'){}
  for(j=0,i;comm[i]!='+';j++,i++){
    protocol[j]=comm[i];
  }
  protocol[j]='\0';
  for(j=0,i++;comm[i]!='+';j++,i++){
    CS[j]=comm[i];
  }
  CS[j]='\0';
  for(j=0,i++;comm[i]!='+';j++,i++){
    port[j]=comm[i];
  }
  port[j]='\0';
  for(j=0,i++;comm[i]!='+';j++,i++){
    IP[j]=comm[i];
  }
  IP[j]='\0';
  setSockANETP(protocol,CS,port,IP);
}
/**
 * @name  user_interrupt
 * @brief This function is used to process interrupt
 * @return void
 ************************************************************/ 
void user_interrupt(){
  char comm[56]={'0'};
  U0_Read();                            //clear U0_READ_REG
  U0_SendChar('*');                     //respond to PC
  getCommPC(comm);                      //get the command
  if(comm[0]=='W'&&comm[1]=='S'){       //tell out and execute command of setting STA
    enterComm();
    setWiFiSTA(comm);
    exitComm();
  }
  if(comm[0]=='W'&&comm[1]=='T'){       //tell out and execute command of setting TCP
    enterComm();
    setWiFiTCP(comm);
    exitComm();
  }
  U0_IrqClr();                          //clear the interrupt
  U0_DataIrq(0);                        //switch off data irq
}
/**
 * @name  main
 * @brief main function
 * @return void
 */
void main(){
  char outputTemp[5]={0};
  char outputHumi[5]={0};
  char comm[56]={'0'};
  int dht11[5]={0};
  int i=0;
  Sys_Irq(1);                         //enable system interrupt
  while(!(comm[0]=='r'&&comm[1]=='#')){           //wait for PC to be ready,the command of PC ready should be "ready#"
    getCommPC(comm);                  //get the command from PC
  }
  U0_SendString("wifi");              //request parameters to initialize WiFiLPT100-WiFi-STA
  getCommPC(comm);                    //get command from PC
  enterComm();
  setWiFiSTA(comm);                   //initialize WiFiLPT100-WiFi-STA
  U0_SendString("atcp");              //request parameters to initialize WiFiLPT100-SockA-TCP
  getCommPC(comm);                    //get command from PC
  setWiFiTCP(comm);                   //initialize WiFiLPT100-SockA-TCP
  exitComm();
  while(1){
    DHT11(dht11);                     //start up DHT11 and get data
    hexToDec(dht11[0],outputHumi);    //convert style from hex to dec
    hexToDec(dht11[2],outputTemp);    //convert style from hex to dec
    /*send the result via WiFiLPT100*/
    U1_SendString("Humidity=");
    U1_SendString(outputHumi);
    U1_SendString("%\t");
    U1_SendString("Temperature=");
    U1_SendString(outputTemp);
    U1_SendString(" Degree Celsius\n");
    /*send the result via serial port*/
    U0_SendString(outputHumi);
    U0_SendChar('+');
    U0_SendString(outputTemp);
    U0_SendChar('\n');
    if(U0_DataReady()){                 //check if there is command from PC
      U0_DataIrq(1);                    //call interrupt process
    }  
    for(i=0;i<240000;i++){}             //delay
  }
}