/**
 * @file compatibility.cpp
 * Implementations of compatibility functions for delays, timers, etc.
 */

#include "compatibility.h"
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_tim.h>

#define M4 4000000


static int multiplier;

static int initialized = 0;

static void init();

static uint64_t ms_counter = 0;

void __msleep(int milisec) {
	if (!initialized) {
		init();
	}
	milisec = 1000 * milisec * multiplier  - 10;
	while(milisec-- > 0) {
		__asm("nop");
	}
}

static void init() {
	RCC_ClocksTypeDef RCC_Clocks;
	RCC_GetClocksFreq(&RCC_Clocks);
	multiplier = RCC_Clocks.HCLK_Frequency / M4;
	initialized = 1;
}

void __usleep(int usec) {
	if (!initialized) {
		init();
	}
	usec = usec * multiplier - 10;
	while(usec--) {
		__asm("nop");
	}
}

void __start_timer() {
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	/* Enable the TIM2 gloabal Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);


	/* TIM2 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 1000 - 1; // 1 MHz down to 1 KHz (1 ms)
	TIM_TimeBaseStructure.TIM_Prescaler = 24 - 1; // 24 MHz Clock down to 1 MHz (adjust per your clock)
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	/* TIM IT enable */
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	/* TIM2 enable counter */
	TIM_Cmd(TIM2, ENABLE);
}

long __millis() {
	return ms_counter;
}

extern "C" void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		ms_counter++;
	}
}
