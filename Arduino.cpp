#include <Bela.h>
#include "Arduino.h" // has to come after BelaArduino because of the #define s it contains

Print Serial;

uint32_t random(uint32_t max)
{
	return random(0, max);
}

void randomSeed(uint32_t s)
{
	srand(s);
}

uint32_t random(uint32_t min, uint32_t max) {
	uint32_t ran = rand();
	return map(ran, 0, (float)RAND_MAX, min, max);
}

uint32_t millis() {
	return micros() / 1000.f;
}

unsigned long micros() {
	static timespec startp;
	static bool inited;
	struct timespec tp;
	clock_gettime(CLOCK_MONOTONIC_RAW, &tp);
	if(!inited) {
		inited = true;
		startp = tp;
		return 0;
	}
	return ((tp.tv_sec - startp.tv_sec) * 1000000 + (tp.tv_nsec - startp.tv_nsec) / 1000.0);
}

#include <unistd.h>
static void splitDelayUs(uint64_t t)
{
	// split across multiple steps so we can return early on a long wait
	size_t step = 100000;
	while(!Bela_stopRequested())
	{
		unsigned int sleep = t >= step ? step : t;
		usleep(sleep);
		t -= sleep;
		if(!t)
			break;
	}
}
void delay(uint32_t t) {
	splitDelayUs(uint64_t(t) * 1000);
}
void delayMicroseconds(uint32_t t)
{
	splitDelayUs(t);
}
void utoa(uint32_t num, char* dest, size_t len) {
	snprintf(dest, len, "%u", num);
}
void noInterrupts() {}
void interrupts() {}
