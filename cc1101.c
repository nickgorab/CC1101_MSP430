/*
 * 		   cc1101.c
 *
 *   Created on:  November 1, 2018
 *  Last Edited:  November 2, 2018
 *       Author:  Nick Gorab,
 *				  Tanner Smith
 *        Board:  MSP430FR2433
 *
 */



void CC1101_Cmd_Strobe(char cmd){
	SPI_Select_CC1101();
	SPI_Send_Byte(cmd);
	SPI_Deselect_CC1101();
}

