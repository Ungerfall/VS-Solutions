#pragma once

#ifndef CRECTANGLE_H
#define CRECTANGLE_H

#include "CShape.h"

//класс треугольник
class CRectangle : public CShape
{
public:
	CRectangle();
	CRectangle(CPoint&, CPoint&, CPoint&);
	std::string Name();
	void About();
	double Square();
	void SetEdge(CPoint&, CPoint&);
	void SetA(CPoint&);
	void SetB(CPoint&);
	void SetC(CPoint&);
	CPoint& GetPointA();
	CPoint& GetPointB();
	CPoint& GetPointC();
	double GetEdgeA();
	double GetEdgeB();
	bool IsRectangle(CRectangle&);
private:
	CPoint a;
	CPoint b;
	CPoint c;
};

#endif