/*
 * 		   uart.h
 *
 *   Created on:  November 1, 2018
 *  Last Edited:  November 2, 2018
 *       Author:  Nick Gorab,
 *				  Tanner Smith
 *        Board:  MSP430FR2433
 *
 */

#include "system.h"

#define DATA_BUFFER_SIZE 240

void UART_A0_Init(int baud);
void UART_A1_Init(int baud);
void UART_Init(int channel, int baud);

void UART_Enable_TX_Int(int channel);
void UART_Enable_R3X_Int(int channel);
void UART_Disable_RX_Int(int channel);
void UART_Disable_TX_Int(int channel);

void UART_Send_Byte(int channel, char data);
void UART_Send_Seq(int channel, char* data, int length);
