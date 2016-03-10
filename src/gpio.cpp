/**
 * @file gpio.cpp
 * @brief non-generic class. Interface for RF24 driver.
 * @version 0.1
 * @author Ivan Pavic
 */
#include "gpio.h"

/** Dummy constant for compatibility **/
#define DUMMY_COMP_CONST 1367

GPIO::GPIO() {
	open(DUMMY_COMP_CONST, DUMMY_COMP_CONST);
}

void GPIO::open(int port,int ddr) {
	init();
}

void GPIO::close(int port) {

}

int GPIO::read(int port) {
	return GPIO_ReadOutputDataBit(GPIOE, SPI_CS);;
}

void GPIO::write(int port, int value) {
	uint16_t pin = (port == 2)? GPIO_Pin_2 : GPIO_Pin_3;
	BitAction bit = (value != 0)? Bit_SET : Bit_RESET;
	GPIO_WriteBit(GPIOE, pin, bit);
}

void GPIO::init() {
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = SPI_CS | NRF_CE;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStruct);
}

GPIO::~GPIO() {
	this->close(1367);
}
