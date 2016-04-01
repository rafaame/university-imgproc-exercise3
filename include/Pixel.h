#ifndef __PIXEL_H__
#define __PIXEL_H__

#include "common.h"

using namespace std;

class Pixel
{

private:

	uint64_t x;
	uint64_t y;
	uint8_t intensity;

	bool processed;

public:

	Pixel(uint64_t x, uint64_t y)
	{

		this->x = x;
		this->y = y;
		this->intensity = 0;

		processed = false;

	}

	uint64_t getX() { return x; }
	uint64_t getY() { return y; }
	uint8_t getIntensity() { return intensity; }
	bool wasProcessed() { return processed; }

	void setX(uint64_t x) { this->x = x; }
	void setY(uint64_t y) { this->y = y; }
	void setIntensity(uint8_t intensity) { this->intensity = intensity; }
	void setProcessed(bool processed) { this->processed = processed; }

	static uint64_t euclidianDistance(Pixel *p1, Pixel *p2);
	static uint64_t mannhatanDistance(Pixel *p1, Pixel *p2);

};

#endif