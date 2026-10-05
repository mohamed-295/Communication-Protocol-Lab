/*
 * SPI.c
 *
 *  Created on: 22 Feb 2023
 *      Author: Alaa Wahba
 */

#include "inc/SPI.h"

void SPI_Init() {
#ifdef MASTER_MODE
	/* GPIO pins Configuration */
	DIO_initPin(MOSI, SPI_PORT, OUTPUT);
    DIO_initPin(MISO, SPI_PORT, INPUT);
    DIO_initPin(SCLK, SPI_PORT, OUTPUT);
    DIO_initPin(SS, SPI_PORT, OUTPUT);

	/* Master Configuration */
	// Enable SPI
	SPCR |= (1 << SPE);
	// Configure it as Master
	SPCR |= (1 << MSTR);
	// shift clock =clk/16
	SPCR |= (1 << SPR0);
	SPCR &= ~(1 << SPR1);
	SPSR &= ~(1 << SPI2X);
	
#endif

#ifdef SLAVE_MODE
	/* GPIO pins Configuration */
	DIO_initPin(MOSI, SPI_PORT, INPUT);
    DIO_initPin(MISO, SPI_PORT, OUTPUT);
    DIO_initPin(SCLK, SPI_PORT, INPUT);
    DIO_initPin(SS, SPI_PORT, INPUT);

	/* Slave Configuration */
	SPCR = (1 << SPE);
	SPCR &= ~(1 << MSTR);

#endif

}
uint8 SPI_SendRecieveData(uint8 Data) {
	SPDR = Data; // send data
	while (!GET(SPSR, SPIF)); // wait until transmission complete
	return SPDR; // return received data
}