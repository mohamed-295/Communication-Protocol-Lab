#include "MCAL/inc/SPI.h"
#include "MCAl/inc/USART.h"
#include "MCAl/inc/Atmega32.h"

#define FRAME_HEADER    0xAA
#define FRAME_TAIL      0x55

#define FRAME_SIZE      8

int main(void)
{
    uint8 frame[FRAME_SIZE];
    uint8 i;

    uint8 day;
    uint8 month;
    uint8 year;

    uint8 hour;
    uint8 minute;
    uint8 second;

    /* Initialize USART for displaying the received data */
    UART_Config_t uart = {9600, 16};
    USART_init(&uart);

    /* Initialize ATmega32 as SPI Slave */
    SPI_Init();

    while (1)
    {
        /*
         * Wait for frame header
         */
        frame[0] = SPI_SendRecieveData(0x00);

        if (frame[0] == FRAME_HEADER)
        {
            /*
             * Receive the remaining frame bytes
             */
            for (i = 1; i < FRAME_SIZE; i++)
            {
                frame[i] = SPI_SendRecieveData(0x00);
            }

            /*
             * Check frame tail
             */
            if (frame[7] == FRAME_TAIL)
            {
                /*
                 * Reassemble date
                 */
                day   = frame[1];
                month = frame[2];
                year  = frame[3];

                /*
                 * Reassemble time
                 */
                hour   = frame[4];
                minute = frame[5];
                second = frame[6];

                /*
                 * Display received date/time over USART
                 */
                printf("Date: %02d/%02d/20%02d\r\n",
                       day,
                       month,
                       year);

                printf("Time: %02d:%02d:%02d\r\n\r\n",
                       hour,
                       minute,
                       second);
            }
        }
    }

    return 0;
}
