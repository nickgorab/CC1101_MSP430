/*
 * 		   uart.c
 *
 *   Created on:  November 1, 2018
 *  Last Edited:  November 2, 2018
 *       Author:  Nick Gorab,
 *				  Tanner Smith
 *        Board:  MSP430FR2433
 *
 */

#include "uart.h"

int* tx0, rx0, tx1, rx1;

struct {
	char rx_data[DATA_BUFFER_SIZE];
	char tx_data[DATA_BUFFER_SIZE];
} uart_data[2];

void UART_A0_Init(int baud) {
	P1SEL0 |= BIT4 | BIT5;

	UCA0CTLW0 |= UCSWRST;		// Puts eUCSI in reset
	UCA0CTLW0 |= UCSSEL__SMCLK;	// Selects SMCLK

	/* Baud Rate Calculation */
	if((FCPU/baud) < 16) {
		UCA0BRW = (FCPU/baud);
	} else {
		UCA0BRW = FCPU / (baud << 4);
		UCA0MCTLW = ((((FCPU << 4) / baud) / 16 - ((FCPU / baud) >> 4) * 16) << 4) + UCOS16;
	}

	UCA0CTLW0 &= ~UCSWRST;		// Takes eUSCI out of reset
}


void UART_A1_Init(int baud) {
	P2SEL0 |= BIT5 | BIT6;

	UCA1CTLW0 |= UCSWRST;		// Puts eUCSI in reset
	UCA1CTLW0 |= UCSSEL__SMCLK;	// Selects SMCLK

	/* Baud Rate Calculation */
	if((FCPU/baud) < 16) {
		UCA1BRW = (FCPU/baud);
	} else {
		UCA1BRW = FCPU / (baud << 4);
		UCA1MCTLW = ((((FCPU << 4) / baud) / 16 - ((FCPU / baud) >> 4) * 16) << 4) + UCOS16;
	}

	UCA1CTLW0 &= ~UCSWRST;		// Takes eUSCI out of reset
}

void UART_Init(int channel, int baud) {
	switch(channel) {
		case 1:
			UART_A0_Init(baud);
			break;
		case 2:
			UART_A1_Init(baud);
			break;
		default:
			break;
	}
}


void UART_Enable_RX_Int(int channel) {
	switch(channel) {
		case 1:
			UCA0IE |= UCRXIE;
			break;
		case 2:
			UCA1IE |= UCRXIE;
			break;
		default:
			break;
	}
}

void UART_Enable_TX_Int(int channel) {
	switch(channel) {
		case 1:
			UCA0IE |= UCTXIE;
			break;
		case 2:
			UCA1IE |= UCTXIE;
			break;
		default:
			break;
	}
}

void UART_Disable_RX_Int(int channel) {
	switch(channel) {
		case 1:
			UCA0IE &= ~UCRXIE;
			break;
		case 2:
			UCA1IE &= ~UCRXIE;
			break;
		default:
			break;
	}
}


void UART_Disable_TX_Int(int channel) {
	switch(channel) {
		case 1:
			UCA0IE &= ~UCRXIE;
			break;
		case 2:
			UCA1IE &= ~UCRXIE;
			break;
		default:
			break;
	}
}




#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void) {
  switch(__even_in_range(UCA0IV,USCI_UART_UCTXCPTIFG))
  {
    case USCI_NONE: break;
    case USCI_UART_UCRXIFG:
      while(!(UCA0IFG&UCTXIFG));
      UCA0TXBUF = UCA0RXBUF;
      __no_operation();
      break;
    case USCI_UART_UCTXIFG: break;
    case USCI_UART_UCSTTIFG: break;
    case USCI_UART_UCTXCPTIFG: break;
    default: break;
  }
}
