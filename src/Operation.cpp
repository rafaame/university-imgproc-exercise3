#include "Operation.h"

#include "Pixel.h"
#include "Image.h"

using namespace std;

Image *Operation::execute(Image *leftOperand/* = NULL*/, void *rightOperand/* = NULL */)
{

	Image *image = NULL;
	Image *result = NULL;

    if(filename.length() > 0)
        image = Image::createFromFile(filename);

	switch(type)
	{

		case OPERATION_INVERT:
		{

			//@FIXME: clone object instead
			result = leftOperand;

            for(int i = 0; i < leftOperand->getHeight(); i++)
                for(int j = 0; j < leftOperand->getWidth(); j++)
                    result->setIntensity(i, j, abs((uint8_t) result->getIntensity(i, j) - 255));

            break;

		}

        case OPERATION_FLOODFILL:
        {

        	result = leftOperand;

        	Pixel *replacementPixel = static_cast<Pixel *>(rightOperand);

     		uint8_t targetIntensity = leftOperand->getIntensity(replacementPixel->getX(), replacementPixel->getY());
     		Pixel *targetPixel = new Pixel(replacementPixel->getX(), replacementPixel->getY());
     		targetPixel->setIntensity(targetIntensity);

     		//cout << "replacementPixel: " << replacementPixel->getX() << " " << replacementPixel->getY() << " " << (uint64_t) replacementPixel->getIntensity() << endl;
     		//cout << "targetPixel: " << replacementPixel->getX() << " " << replacementPixel->getY() << " " << (uint64_t) targetIntensity << endl;

     		if(targetIntensity == replacementPixel->getIntensity())
     			break;

     		queue<Pixel *> processedPixels;
     		queue<Pixel *> q;
     		q.push(targetPixel);

     		while(!q.empty())
     		{

     			Pixel *p = q.front();
     			q.pop();

     			//cout << "Iteration: " << p->getX() << " " << p->getY() << " " << (uint64_t) p->getIntensity() << endl;

     			if(p->getIntensity() == targetIntensity)
     			{

     				//cout << "    new intensity: " << (uint64_t) replacementPixel->getIntensity() << endl;

     				result->setIntensity(p->getX(), p->getY(), replacementPixel->getIntensity());
     				
     				p->setProcessed(true);
     				processedPixels.push(p);

     				if(p->getX() > 0)
     				{

     					Pixel *west = new Pixel(p->getX() - 1, p->getY());
     					west->setIntensity(result->getIntensity(west->getX(), west->getY()));

     					q.push(west);

     					//cout << "    west: " << west->getX() << " " << west->getY() << " " << (uint64_t) west->getIntensity() << endl;

     				}

     				if(p->getX() < (result->getWidth() - 1))
     				{

     					Pixel *east = new Pixel(p->getX() + 1, p->getY());
     					east->setIntensity(result->getIntensity(east->getX(), east->getY()));

     					q.push(east);

     					//cout << "    east: " << east->getX() << " " << east->getY() << " " << (uint64_t) east->getIntensity() << endl;

     				}

     				if(p->getY() > 0)
     				{

     					Pixel *north = new Pixel(p->getX(), p->getY() - 1);
     					north->setIntensity(result->getIntensity(north->getX(), north->getY()));

     					q.push(north);

     					//cout << "    north: " << north->getX() << " " << north->getY() << " " << (uint64_t) north->getIntensity() << endl;

     				}

     				if(p->getY() < (result->getHeight() - 1))
     				{

     					Pixel *south = new Pixel(p->getX(), p->getY() + 1);
     					south->setIntensity(result->getIntensity(south->getX(), south->getY()));

     					q.push(south);

     					//cout << "    south: " << south->getX() << " " << south->getY() << " " << (uint64_t) south->getIntensity() << endl;

     				}

     			}

     			//cout << endl;

     		}

     		while(!processedPixels.empty())
     		{

     			Pixel *p = processedPixels.front();

     			delete p;
     			processedPixels.pop();

     		}

        	break;

        }

		default:
		{

			result = image;

		}

	}

	return result;

}