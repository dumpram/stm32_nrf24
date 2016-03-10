#include "usart.h"

void retarget_init() {
  init_USART1(9600);
}

extern "C" int _write (int fd, char *ptr, int len) {
  	while(*ptr && (len--)) {
		//waits until USART1 is ready
		while(!(USART1->SR & 0x40));
		USART_SendData(USART1, *ptr);
		ptr++;
	}
	return len;
}


// TO - DO
extern "C" int _read (int fd, char *ptr, int len)
{
  /* Read "len" of char to "ptr" from file id "fd"
   * Return number of char read.
   * Need implementing with UART here. */
  return len;
}

// TO - DO
extern "C" void _ttywrch(int ch) {
  /* Write one char "ch" to the default console
   * Need implementing with UART here. */
}


