/*--------------------------------------------------------------------
 * TITLE: Custom Functions
 * AUTHOR: DaiZhirui
 * DATE CREATED: 2017-04-29
 * FILENAME: ASTRO.h
 * PROJECT: M2 Laboratory
 * COPYRIGHT: DaiZhirui
 * DESCRIPTION:
 *    Custom functions based on reading and writing the registers of M2
 *    The functions in this repository is tested by DaiZhirui
 * MODIFICATION HISTORY:
 *  2017-04-29: added U0_Read, U0_Send, U0_LinMaster, U0_LinSlave
 *              U1_Read, U1_Send, U1_LinMaster, U1_LinSlave
 *  2017-05-15: added U1_SendString, U1_SendString
 *--------------------------------------------------------------------*/
#ifndef __ASTRO_H__
#define __ASTRO_H__
/**************************Uart&Lin Functions**************************/
long U0_Read();
void U0_SendChar(char c);
void U0_SendInt(int c);
void U0_SendString(char* c);
void U0_LinMaster(int brklength);
void U0_LinSlave();
long U1_Read();
void U1_SendChar(char c);
void U1_SendInt(int c);
void U1_SendString(char* c);
void U1_LinMaster(int brklength);
void U1_LinSlave();
/**********************Uart&Lin Functions END**************************/
#endif
