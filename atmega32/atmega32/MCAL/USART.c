/*
 * USART.c
 *
 *  Created on: 13 Feb 2023
 *      Author: Alaa Wahba
 */

#include "inc/USART.h"
#define Default_Stop 		'\r'
static uint32 flag = 1;
static uint8 *TX_str;


void USART_init(UART_Config_t *pinConfig) {
	/*   Baud rate   */
	uint16 UBRR = (F_CPU / (16 * pinConfig->baudRate)) - 1;
	//  110 0110 001
	UCSRC &= ~(1 << URSEL);
	UBRRL = (uint8) UBRR;
	UBRRH = (uint8) (UBRR >> 8);

	/*  FRAME 	  */
	//This bit selects  Asynchronous
	UCSRC |= (1 << URSEL);
	UCSRC &= ~(1 << UMSEL);
	
	//These bits enable and set type of parity generation (No parity )
	UCSRC &= ~(1 << UPM0);
	UCSRC &= ~(1 << UPM1);

	//This bit selects the number of Stop Bits to be inserted by the Transmitter (1 bit)
	UCSRC &= ~(1 << USBS);

	// sets the number of data bits (8 bits by default)
	UCSRC |= (1 << UCSZ0);
	UCSRC |= (1 << UCSZ1);
	UCSRB &= ~(1 << UCSZ2);

	/*   Enable  */
	UCSRB |= (1 << RXEN); // Enable receiver
	UCSRB |= (1 << TXEN); // Enable transmitter
}

void USART_send(uint8 data) {
	//The transmit buffer can only be written when the UDRE Flag in the UCSRA Register is set.
	while (!GET(UCSRA, UDRE))
		;
	UDR = data;
}

uint8 USART_recieve() {
	/*
	 * This flag bit is set when there are unread data in the receive buffer
	 * and cleared when the receive buffer is empty
	 */
	while (!GET(UCSRA, RXC));
	return UDR;
}

void USART_sendNumber(uint32 data) {

	char str[7];

	sprintf(str, "%d", data);  // Adjust the formatting to your liking.

	USART_sendString(str);

}

uint32 USART_recieveNumber() {
	uint32 num;
	return num;
}

void USART_sendString(uint8 *str) {
	for (uint8 i = 0; i < str[i]; i++)
		USART_send(str[i]);

	USART_send(Default_Stop);
}

void USART_recieveString(uint8 *Buff) {

	uint8 i = 0;
	Buff[i] = USART_recieve();
	while (Buff[i] != Default_Stop) {
		i++;
		Buff[i] = USART_recieve();
	}
	Buff[i] = '\0';
}