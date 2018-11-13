/*
 * 		   spi.c
 *
 *   Created on:  November 1, 2018
 *  Last Edited:  November 2, 2018
 *       Author:  Nick Gorab,
 *				  Tanner Smith
 *        Board:  MSP430FR2433
 *
 */

#include "spi.h"

void SPI_A0_Init() {

	/************************\
	* P1.4 = UCA0SIMO		 *
	* P1.5 = UCA0SOMI		 *
	* P1.6 = UCA0CLK		 *
	\************************/

	P1SEL0 |= BIT4 | BIT5 | BIT6;	// Pin selects

	UCA0CTLW0 |= UCSWRST;			// eUSCI logic held in reset state 
    UCA0CTLW0 |= UCMSB          	// Sends MSB of data first
              |  UCMST          	// Selects master mode
              |  UCSYNC         	// Synchronous mode
              |  UCCKPH         	// Data captured on first UCLK edge and change on the following edge
              |  UCMODE_0;      	// 3-pin SPI mode
    UCA0CTLW0 |= UCSSEL__SMCLK;		// Sub-main clock
	
    UCA0BR0   = 0x01;				// fclk = fbrclk/(UCBRx+1)
    UCA0BR1   = 0;					// Bit clock pre-scaler of 0
    UCA0MCTLW = 0;					// 
	
    UCA0CTLW0 &= ~UCSWRST;			// Takes eUSCI out of reset state 
}



void SPI_A1_Init() {

	/************************\
	* P2.6 = UCA0SIMO		 *
	* P2.5 = UCA0SOMI		 *
	* P2.4 = UCA0CLK		 *
	\************************/

	P2SEL0 |= BIT4 | BIT5 | BIT6;	// Pin selects

	UCA1CTLW0 |= UCSWRST;			// eUSCI logic held in reset state 
    UCA1CTLW0 |= UCMSB          	// Sends MSB of data first
              |  UCMST          	// Selects master mode
              |  UCSYNC         	// Synchronous mode
              |  UCCKPH         	// Data captured on first UCLK edge and change on the following edge
              |  UCMODE_0;      	// 3-pin SPI mode
    UCA1CTLW0 |= UCSSEL__SMCLK;		// Sub-main clock
	
    UCA1BR0   = 0x01;				// fclk = fbrclk/(UCBRx+1)
    UCA1BR1   = 0;					// Bit clock pre-scaler of 0
    UCA1MCTLW = 0;					// 
	
    UCA1CTLW0 &= ~UCSWRST;			// Takes eUSCI out of reset state 
}



void SPI_B0_Init() {

	/************************\
	* P1.2 = UCA0SIMO		 *
	* P1.3 = UCA0SOMI		 *
	* P1.1 = UCA0CLK		 *
	\************************/

	P1SEL0 |= BIT1 | BIT2 | BIT3;	// Pin selects

	UCB0CTLW0 |= UCSWRST;       	// eUSCI logic held in reset state
    UCB0CTLW0 |= UCMSB          	// Sends MSB of data first
              |  UCMST          	// Selects master mode
              |  UCSYNC         	// Synchronous mode
              |  UCCKPH         	// Data captured on first UCLK edge and change on the following edge
              |  UCMODE_0;      	// 3-pin SPI mode
    UCB0CTLW0 |= UCSSEL__SMCLK;

    UCB0BR1 = 0;                	// Bit clock pre-scaler of 0.
    UCB0CTLW0 &= ~UCSWRST;      	// Takes eUSCI out of reset state
}



void SPI_Channel_Init(int channel) {
	switch(channel) {		
		case 1:				// Channel 1
			SPI_A0_Init();
			break;
		case 2:				// Channel 2
			SPI_A1_Init();
			break;
		case 3:				// Channel 3
			SPI_B0_Init();
			break;
		default:
			break;
	}
}



void SPI_Enable_RX_Int(int channel) {
	switch(channel) {
		case 1:					// Channel 1
			UCA0IE |= UCRXIE;
			break;
		case 2:					// Channel 2
			UCA1IE |= UCRXIE;
			break;
		case 3:					// Channel 3
			UCB0IE |= UCRXIE;
			break;
		default:
			break;
	}
}

void SPI_Disable_RX_Int(int channel) {
	switch(channel) {
		case 1:
			UCA0IE &= ~UCRXIE;
			break;
		case 2:
			UCA1IE &= ~UCRXIE;
			break;
		case 3:
			UCB0IE &= ~UCRXIE;
			break;
		default:
			break;
	}
}



void SPI_Enable_TX_Int(int channel) {
	switch(channel) {
		case 1:
			UCA0IE |= UCTXIE;
			break;
		case 2:
			UCA1IE |= UCTXIE;
			break;
		case 3:
			UCB0IE |= UCTXIE;
			break;
		default:
			break;
	}
}


void SPI_Disable_TX_Int(int channel) {
	switch(channel) {
		case 1:
			UCA0IE &= ~UCTXIE;
			break;
		case 2:
			UCA1IE &= ~UCTXIE;
			break;
		case 3:
			UCB0IE &= ~UCTXIE;
			break;
		default:
			break;
	}
}


void SPI_Select(unsigned int pin) {

	char pinouts[] = {8, 8, 4, 5, 6, 7, 0, 1,	// Array of pin numbers
	 				  2, 3, 2, 0, 3, 1, 4, 5, 
	 				  6, 8, 7, 2, 0, 1, 8, 8};

	if(pin < 11) {								// Port 1
		P1OUT |= pinouts[pin];
	} else if (pin == 12 | 13 | 20) {			// Port 3
		P3OUT |= pinouts[pin];
	} else if (pin == 1 | 2 | 23 | 24) {		// Unassigned
		// Do nothing
	} else {									// Port 2
		P2OUT |= pinouts[pin];
	}
}



void SPI_Deselect(unsigned int pin) {

	char pinouts[] = {8, 8, 4, 5, 6, 7, 0, 1,	// Array of pin numbers
	 				  2, 3, 2, 0, 3, 1, 4, 5, 
	 				  6, 8, 7, 2, 0, 1, 8, 8};

	if(pin < 11) {								// Port 1
		P1OUT &= ~pinouts[pin];
	} else if (pin == 12 | 13 | 20) {			// Port 3
		P3OUT |= ~pinouts[pin];
	} else if (pin == 1 | 2 | 23 | 24) {		// Unassigned
		// Do nothing
	} else {									// Port 2
		P2OUT |= ~pinouts[pin];
	}
}

void SPI_Send_Byte(int channel, char data) {
	switch(channel) {
		case 1:
			UCA0TXBUF = data;
			while(UCA0STATW & UCBUSY);
		break;
	}
}
