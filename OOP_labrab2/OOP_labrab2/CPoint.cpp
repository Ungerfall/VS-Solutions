#include "CPoint.h"

CPoint::CPoint()
	:x(0), y(0){}

CPoint::CPoint(coordinate x, coordinate y)
	:x(x), y(y){}

coordinate CPoint::GetX()
{
	return this->x;
}

coordinate CPoint::GetY()
{
	return this->y;
}