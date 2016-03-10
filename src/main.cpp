/**
 * @file main.cpp
 * @brief Main test program for STM32F4xx and RF24
 * @dependencies std_periph_drivers
 * @used SPI2, GPIOE (Pins 2 & 3), USART1, printf (retargeted to USART1 @ref
 * retarget.cpp), TIM2 for simulation of __millis() function
 */
#include "stm32f4xx.h"
#include "RF24.h"
#include "compatibility.h"
#include "usart.h"
#include "gpio.h"
#include "retarget.h"

/** Host nRF24 address **/
static const uint64_t extAddress = 0xF0F0F0F0E2LL;

/** Test message **/
static char message[] = "F0F0F0F0D3:TestNRF!\n";

/**
 * Function setups RF24 radio. Additionally prints out registers.
 */
void setupRF(RF24 &radio) {
    radio.begin();
    radio.setChannel(0x4C);
    radio.setPayloadSize(32);
    radio.setPALevel(RF24_PA_LOW);
    radio.openWritingPipe(extAddress);
    radio.printDetails();
}
/**
 * Main function.
 */
int main() {
    retarget_init();
	printf("Boot...\n");
    RF24 rf24(2,3);
	setupRF(rf24);
    /** Initialize LED for testing purposes and debugging **/
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;  // enable the clock to GPIOD
    __asm("dsb");                         // stall instruction pipeline, until instruction completes, as                                        //    per Errata 2.1.13, "Delay after an RCC peripheral clock enabling"
    GPIOD->MODER = (1 << 26);             // set pin 13 to be general purpose output
    while (1367) {
        __msleep(500);
        GPIOD->ODR ^= (1 << 13);           // Toggle the pin
        rf24.write(message, sizeof(char) * strlen(message));
    }
}
