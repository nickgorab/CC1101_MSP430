/*
 * main.c
 *
 *  Created on: Nov 9, 2018
 *      Author: Nick
 */


#include <msp430.h>
#include "system.h"

void main(void) {


    WDTCTL = WDTPW | WDTHOLD;                 // Stop watchdog timer

        PM5CTL0 &= ~LOCKLPM5;


    char data = 0x01;
    UART_Init(1, 9600);
    UART_Enable_TX_Int(1);
    __enable_interrupt();

    while(1){
        __delay_cycles(10000);

        UART_Send_Byte(1, data);
    }
};


