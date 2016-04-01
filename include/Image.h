#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "common.h"

using namespace std;

class Image
{

private:

	uint64_t width;
	uint64_t height;
	//uint8_t **data;
	uint32_t **data;

public:

	Image(uint64_t width, uint64_t height);
	~Image();

	uint64_t getWidth() { return width; }
	uint64_t getHeight()  { return height; }
	uint8_t getIntensity(uint64_t x, uint64_t y) { return data[x][y]; }

	void setIntensity(uint64_t x, uint64_t y, uint8_t intensity)
	{

		if(x > height || y > width)
		{

			cerr << "[Image::setIntensity] Error: out of range" << endl;
			return;

		}

		data[x][y] = intensity;

	}

    bool writeToFile(string filename);
	static Image *createFromFile(string filename);

	uint8_t getMaxIntensity();
	map<uint8_t, uint64_t> getIntensityFrequencies();
	uint8_t getIntensityMean();
	uint8_t getIntensityStandardDeviation();

};

#endif