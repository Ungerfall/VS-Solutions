#pragma once

#ifndef CPOINT_H
#define CPOINT_H

typedef double coordinate;

//����� �����
class CPoint
{
public:
	CPoint(coordinate, coordinate);
	CPoint();
	coordinate GetX();
	coordinate GetY();
private:
	coordinate x;
	coordinate y;
};

#endif