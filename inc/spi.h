#ifndef SPI_H
#define	SPI_H

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

#include <cstdint>
#include <string>

using namespace std;

class SPI {
	public:
		SPI();
		uint8_t transfer(uint8_t tx_);
		virtual ~SPI();

	private:
		std::string device;
		uint8_t mode;
		uint8_t bits;
		uint32_t speed;
		int fd;
		void init();
};
#endif
