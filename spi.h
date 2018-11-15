/*
 * 		   spi.h
 *
 *   Created on:  November 1, 2018
 *  Last Edited:  November 2, 2018
 *       Author:  Nick Gorab,
 *				  Tanner Smith
 *        Board:  MSP430FR2433
 *
 */

#ifndef SPI_H
#define SPI_H

#include <msp430.h>

void SPI_A0_Init();
void SPI_A1_Init();
void SPI_B0_Init();
void SPI_Channel_Init(int channel);

void SPI_Enable_RX_Int(int channel);
void SPI_Enable_TX_Int(int channel);
void SPI_Disable_RX_Int(int channel);
void SPI_Disable_TX_Int(int channel);

void SPI_Select(unsigned int pin);
void SPI_Deselect(unsigned int pin);

void SPI_Send_Byte(int channel, char data);
void SPI_Send_Seq(int channel, char* data, int length);

void SPI_Read_Byte(int channel, char* reply);
void SPI_Read_Seq(int channel, char* reply);

#endif /* SPI_H */

