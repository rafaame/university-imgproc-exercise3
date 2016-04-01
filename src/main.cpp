#include "common.h"
#include "Pixel.h"
#include "Image.h"
#include "Operation.h"

using namespace std;

int main(int argc, char *argv[])
{

	if(argc < 4)
	{

		cout << "Usage: main /path/to/pgm/image x1,y1 i";

		return 0;

	}

	char *arg = argv[1];
	string filename = string(arg);

	char *coordArg = argv[2];
	string coordStr = string(coordArg);
	uint64_t x = atol(coordStr.substr(0, coordStr.find(",")).c_str());
	uint64_t y = atol(coordStr.substr(coordStr.find(",") + 1).c_str());

	Pixel *p = new Pixel(x, y);
	p->setIntensity((uint8_t) atoi(argv[3]));

	Image *image = NULL;

	Operation *openImage = new Operation(OPERATION_NONE, filename);
	image = openImage->execute();

	Operation *floodFill = new Operation(OPERATION_FLOODFILL);
	image = floodFill->execute(image, static_cast<void *>(p));

	image->writeToFile("output.pgm");

	return 0;

}