#include "Image.h"

using namespace std;

Image *Image::createFromFile(string filename)
{

	string line;
	ifstream file(filename, ios::in | ios::binary);

	if(file.is_open())
	{

		if(file.good())
		{

			getline(file, line);

			if(/*line.compare("P2") == 0*/ true)
			{


				streampos seek = file.tellg();
				while(getline(file, line))
				{

					if(line[0] != '#')
						break;
					else
						seek = file.tellg();

				}

				file.seekg(seek);

				stringstream ss;
				ss << file.rdbuf();

				uint64_t width = 0, height = 0, unknown = 0;
				ss >> width >> height >> unknown;

				if(width > 0 && height > 0)
				{

					Image *image = new Image(width, height);

                    uint8_t *buffer = new uint8_t[width * height];

                    ss.read(reinterpret_cast<char *>(buffer), width * height * sizeof(uint8_t));

					for(int i = 0; i < width; i++)
						for(int j = 0; j < height; j++)
						{

                            image->data[i][j] = (uint8_t) buffer[j * width + i];

                            //if(image->data[i][j] == 255)
                            //	cout << "255: " << i << " " << j << endl;

						}

					return image;

				}

			}

		}

	}

	return NULL;

}

bool Image::writeToFile(string filename)
{

    string line;
    ofstream file(filename, ios::out | ios::binary);

    if(!file.is_open())
        return false;

    if(!file.good())
        return false;

    file << "P5" << endl;
    file << width << " " << height << endl;
    file << 255 << endl;

    for(uint64_t i = 0; i < height; i++)
    {

        char *buffer = new char[width];

        for(uint64_t j = 0; j < width; j++)
            buffer[j] = (uint8_t) data[j][i];

        file.write((const char *) buffer, width);

    }

    file.close();

    return true;

}

Image::Image(uint64_t width, uint64_t height)
{

	this->width = width;
	this->height = height;

	data = new uint32_t *[width];

	for(int i = 0; i < width; i++)
		data[i] = new uint32_t[height];

}

Image::~Image()
{

	delete[] data;
	data = NULL;

}

uint8_t Image::getMaxIntensity()
{

	uint8_t maxIntensity = 0;

	for(int i = 0; i < width; i++)
		for(int j = 0; j < height; j++)
			if(data[i][j] > maxIntensity)
				maxIntensity = data[i][j];

	return maxIntensity;

}

map<uint8_t, uint64_t> Image::getIntensityFrequencies()
{

	map<uint8_t, uint64_t> intensityFrequencies;

	for(int i = 0; i < width; i++)
		for(int j = 0; j < height; j++)
		{

			uint8_t intensity = data[i][j];

			auto it = intensityFrequencies.find(intensity);
			if(it == intensityFrequencies.end())
				intensityFrequencies.insert(pair<uint8_t, uint64_t>(intensity, 0));

			intensityFrequencies[intensity]++;

		}

	return intensityFrequencies;

}

uint8_t Image::getIntensityMean()
{

	uint64_t mean = 0;

	for(int i = 0; i < width; i++)
		for(int j = 0; j < height; j++)
			mean += data[i][j];

	mean /= width * height;

	return mean;

}

uint8_t Image::getIntensityStandardDeviation()
{

	uint8_t mean = getIntensityMean();
	uint64_t standardDeviation = 0;

	for(int i = 0; i < width; i++)
		for(int j = 0; j < height; j++)
			standardDeviation += (data[i][j] - mean) * (data[i][j] - mean);

	standardDeviation /= width * height;

	return sqrt(standardDeviation);

}