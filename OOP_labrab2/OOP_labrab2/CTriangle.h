#pragma once

#ifndef CTRIANGLE_H
#define CTRIANGLE_H

#include "CShape.h"

using namespace std;

//класс треугольник
class CTriangle : public CShape
{
public:
	CTriangle();
	CTriangle(CPoint&, CPoint&, CPoint&);
	std::string Name();
	void About();
	double Square();
	void SetEdge(CPoint&, CPoint&, CPoint&);
	void SetA(CPoint&);
	void SetB(CPoint&);
	void SetC(CPoint&);
	CPoint& GetPointA();
	CPoint& GetPointB();
	CPoint& GetPointC();
	double GetEdgeA();
	double GetEdgeB();
	double GetEdgeC();
private:
	CPoint a;
	CPoint b;
	CPoint c;
};

#endif