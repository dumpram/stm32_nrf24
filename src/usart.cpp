#include "usart.h"

/**
* Function initialises USART1 with given baudrate.
* @param baudrate given baudrate
* */
void init_USART1(int baudrate) {
	/* GPIO structure for initialisation */
	GPIO_InitTypeDef GPIO_InitStruct;
	/* USART structure for initalisation */
	USART_InitTypeDef USART_InitStruct;
	/* NVIC structure for initalisation */
	NVIC_InitTypeDef NVIC_InitStruct;
	/* For USART1 enable clock on APB2 bus*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); 
	/* For GPIOB enable clock on AHB1 bus  */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);	
	
	/* Forming GPIO structure */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; //pin 6(TX), pin7(RX) 
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF; 			
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;			
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	
	/* Initalization of GPIO */
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	/* Give USART1 control over GPIOB pins 6 and 7*/
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1); 
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);
	
	/* Forming USART initalisation structure */
	USART_InitStruct.USART_BaudRate = baudrate;				
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;		
	USART_InitStruct.USART_Parity = USART_Parity_No;		
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; 
	
	/* Initialisation of USART1 */
	USART_Init(USART1, &USART_InitStruct);				
	
	/* Enabling interrupt for USART1 */
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); 
	
	/* Forming NVIC structure */
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn; 
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0; 
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;	
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE; 
	/* NVIC initialisation */
	NVIC_Init(&NVIC_InitStruct);	
	/* Enabling USART1 */
	USART_Cmd(USART1, ENABLE);
}

void USART_puts(USART_TypeDef* USARTx, char* bytes) {
	while(*bytes) {
		//waits until USART1 is ready
		while(!(USART1->SR & 0x40));
		USART_SendData(USARTx, *bytes);
		bytes++;
	}
}

extern "C" void USART1_IRQHandler(void) {
  //checks if interrupt is set by USART1 
  if(USART_GetITStatus(USART1, USART_IT_RXNE)) {
    char byteReceived = USART1->DR;
    USART_puts(USART1, &byteReceived); 
  }
}

