#include "Pixel.h"

using namespace std;

uint64_t Pixel::euclidianDistance(Pixel *p1, Pixel *p2)
{

	uint64_t deltaX = p2->getX() - p1->getX();
	uint64_t deltaY = p2->getY() - p1->getY();

	return (uint64_t) sqrt(deltaX * deltaX + deltaY * deltaY);

}

uint64_t Pixel::mannhatanDistance(Pixel *p1, Pixel *p2)
{

	uint64_t deltaX = abs((int64_t) p2->getX() - (int64_t) p1->getX());
	uint64_t deltaY = abs((int64_t) p2->getY() - (int64_t) p1->getY());

	return (uint64_t) (deltaX + deltaY);

}