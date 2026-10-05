#include <Wire.h>
#include <SPI.h>
#include <RTClib.h>

RTC_DS3231 rtc;

#define SS_PIN       10

#define FRAME_HEADER 0xAA
#define FRAME_TAIL   0x55


void setup()
{
    Serial.begin(9600);

    /*
     * Initialize I2C
     */
    Wire.begin();

    /*
     * Initialize RTC
     */
    if (!rtc.begin())
    {
        Serial.println("RTC not found!");
        while (1);
    }


    /*
     * Initialize SPI
     */
    SPI.begin();

    /*
     * Arduino is SPI Master
     */
    pinMode(SS_PIN, OUTPUT);

    /*
     * Slave deselected initially
     */
    digitalWrite(SS_PIN, HIGH);


    /*
     * SPI configuration
     *
     * ATmega driver:
     * CPOL = 0
     * CPHA = 0
     * MSB first
     *
     * SPI clock = F_CPU / 16
     */
    SPI.beginTransaction(
        SPISettings(
            62500,
            MSBFIRST,
            SPI_MODE0
        )
    );


    Serial.println("System initialized.");
}


void loop()
{
    /*
     * Read RTC
     */
    DateTime now = rtc.now();


    /*
     * Convert year to two digits
     *
     * 2026 -> 26
     */
    uint8_t year = now.year() % 100;


    /*
     * Select ATmega32
     */
    digitalWrite(SS_PIN, LOW);


    /*
     * Send frame
     */

    SPI.transfer(FRAME_HEADER);

    SPI.transfer(now.day());

    SPI.transfer(now.month());

    SPI.transfer(year);

    SPI.transfer(now.hour());

    SPI.transfer(now.minute());

    SPI.transfer(now.second());

    SPI.transfer(FRAME_TAIL);


    /*
     * Deselect ATmega32
     */
    digitalWrite(SS_PIN, HIGH);


    /*
     * Debug on Arduino Serial Monitor
     */
    Serial.print("Sent: ");

    Serial.print(now.day());
    Serial.print("/");

    Serial.print(now.month());
    Serial.print("/");

    Serial.print(now.year());

    Serial.print(" ");

    Serial.print(now.hour());
    Serial.print(":");

    Serial.print(now.minute());
    Serial.print(":");

    Serial.println(now.second());


    /*
     * Send every 1 second
     */
    delay(1000);
}