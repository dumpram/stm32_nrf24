#ifndef _GPIO_H_
#define _GPIO_H_

#include <stm32f4xx_gpio.h>

#define SPI_CS GPIO_Pin_3
#define NRF_CE GPIO_Pin_2

#define NRF_GPIO (GPIO_TypeDef*) GPIOE

class GPIO {
public:

	/* Constants */
	static const int DIRECTION_OUT = 1;
	static const int DIRECTION_IN = 0;

	static const int OUTPUT_HIGH = 1;
	static const int OUTPUT_LOW = 0;

	GPIO();
	/**
	 *
     * @param port
     * @param DDR
     */
	static void open(int port, int DDR);
	/**
	 *
     * @param port
     */
	static void close(int port);
	/**
	 *
     * @param port
     * @param value
     */
	static int read(int port);
	/**
	*
	* @param port
	* @param value
	*/
	static void write(int port,int value);

	virtual ~GPIO();

private:
	static void init();

};

#endif /* _GPIO_H_ */
