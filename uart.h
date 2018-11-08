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



void UART_A0_Init(int baud, int FCPU);
void UART_A1_Init(int baud, int FCPU);
void UART_Init(int channel, int baud, int FCPU);

void UART_Enable_TX_Int(int channel);
void UART_Enable_R3X_Int(int channel);
void UART_Disable_RX_Int(int channel);
void UART_Disable_TX_Int(int channel);


struct {
	char rx_data[DATA_BUFFER_SIZE];
	char rx_data[DATA_BUFFER_SIZE];
} uart_data[2]	// Change this number to include more UART channels