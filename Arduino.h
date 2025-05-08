#pragma once

#define ARDUINO 100

#include <stdint.h>
#define pgm_read_byte(ADDR) (*(ADDR))
#define F(...) __VA_ARGS__

#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105

#ifndef NULL
#define NULL nullptr
#endif // NULL
#define PROGMEM
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>

#define HEX "#x"
#define DEC "d"
#define OCT "o"
#define BIN "BINARY"
void setup();
void loop();
struct Print {
	void begin(uint32_t rate) {};
	template <typename T>
	void print(T arg, const char* format)
	{
		if(!std::is_integral<T>::value)
			return;
		char const* ourformat = nullptr;
		if(0 == strcmp(format, BIN))
		{
			for(size_t n = 0; n < sizeof(T); ++n)
				printf("%d", (arg >> (sizeof(T) - n - 1)) & 1);
			return;
		}
		if(0 == strcmp(format, HEX))
			ourformat = "%" HEX;
		else if(0 == strcmp(format, DEC))
			ourformat = "%" DEC;
		else if(0 == strcmp(format, OCT))
			ourformat = "%" OCT;
		if(ourformat)
			printf(ourformat, arg);
	}
	template <typename T>
	void print(T arg, unsigned int precision = -1)
	{
		static const auto default_precision{std::cout.precision()};
		if(-1 != precision)
		{
			std::cout << std::setprecision(precision);
		}
		std::cout << arg;
		if(-1 != precision)
		{
			std::cout << std::setprecision(default_precision);
		}
	}
	template <typename T, typename U = unsigned>
	void println(T arg = "", U format = -1)
	{
		print(arg, format);
		print("\n");
	}
	operator bool()
	{
		return true;
	}
	void write(const void* buf, size_t len)
	{
		fwrite(buf, len, 1, stdout);
	}
	void write(uint8_t c)
	{
		write(&c, sizeof(c));
	}
	void write(const char* str)
	{
		print(str);
	}
};

extern Print Serial;
#include <libraries/Gui/Gui.h>
extern Gui gui;

unsigned long micros();
uint32_t millis();
uint32_t random(uint32_t max);
uint32_t random(uint32_t min, uint32_t max);
void randomSeed(uint32_t s);
void delay(uint32_t);
void delayMicroseconds(uint32_t);
#define LED_BUILTIN 0
#define INPUT 0
#define OUTPUT 1
#define INPUT_PULLUP 0
#define OUTPUT_PULLUP 0
#define LOW 0
#define HIGH 1
void pinMode(uint32_t, uint32_t);
bool digitalRead(uint32_t);
void digitalWrite(uint32_t, bool);
void pwmWrite(uint32_t, float, float = 172);
float analogRead(uint32_t);
void analogWrite(uint32_t, float);
#define LSBFIRST 0
#define MSBFIRST 1
void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t latchPin, uint8_t bitOrder, uint8_t numBits, uint32_t val);

typedef char __FlashStringHelper;
typedef uint8_t byte;
#define strlen_P strlen
#include <Utilities.h>
void utoa(uint32_t, char*, size_t);
void noInterrupts();
void interrupts();

#define PSTR(a) (a)
#include <pthread.h>
#define yield() pthread_yield()
