/*
 * SPI_Master.c
 *
 * Created: 25/09/2026 11:05:00 PM
 * Author : Alaa
 */ 

#include <avr/io.h>

#include "SPI.h"
#include <util/delay.h>

int main(void)
{
   
   uint8 ch = 0;

   DDRA = 0xFF;      /* PORTA as output -> LEDs show the slave's reply */

   SPI_Init();

   DIO_WritePin(SS, SPI_PORT, LOW);   /* select the slave for the whole demo */

   for (ch = 0; ch <= 255; ch++) {
	   _delay_ms(1000);
	   PORTA = SPI_SendRecieveData(ch);
   }

   DIO_WritePin(SS, SPI_PORT, HIGH);  /* deselect when the count finishes */
}

