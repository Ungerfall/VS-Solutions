#pragma once

#ifndef CELLIPSE_H
#define CELLIPSE_H

#include "CShape.h"

using namespace std;

//класс треугольник
class CEllipse : public CShape
{
public:
	CEllipse();
	CEllipse(CPoint&, CPoint&, CPoint&);
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
private:
	CPoint a;
	CPoint b;
	CPoint c;
};

#endif