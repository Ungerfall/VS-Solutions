#include "CTriangle.h"

using namespace std;

CTriangle::CTriangle()
	:a(CPoint(0, 3)), b(CPoint(0, 0)), c(CPoint(3, 0)) {}

//конструктор
CTriangle::CTriangle(CPoint& a, CPoint& b, CPoint& c)
	:a(a), b(b), c(c) {}

std::string CTriangle::Name()
{
	return "Треугольник";
}

void CTriangle::About()
{
	cout << "\nФигура: " << "\t" << this->Name() << endl;
	cout << "Длины сторон:" << endl;
	cout << "a:\t\t" << this->GetEdgeA() << endl;
	cout << "b:\t\t" << this->GetEdgeB() << endl;
	cout << "c:\t\t" << this->GetEdgeC() << endl;
	cout << "Площадь:" << "\t" << this->Square();
}

double CTriangle::Square()
{
	double sqr;
	sqr = 0.5 * ((this->b.GetX() - this->a.GetX()) * (this->c.GetY() - this->a.GetY()) - ((this->c.GetX() - this->a.GetX()) * (this->b.GetY() - this->a.GetY())));
	return abs(sqr);
}

//установка сторон
void CTriangle::SetEdge(CPoint& a, CPoint& b, CPoint& c)
{
	this->a = a;
	this->b = b;
	this->c = c;
}

//установка стороны А
void CTriangle::SetA(CPoint& a)
{
	this->a = a;
}

//установка стороны B
void CTriangle::SetB(CPoint& b)
{
	this->b = b;
}

//установка стороны C
void CTriangle::SetC(CPoint& c)
{
	this->c = c;
}

//получение точки А
CPoint& CTriangle::GetPointA()
{
	return this->a;
}

//получение точки B
CPoint& CTriangle::GetPointB()
{
	return this->b;
}

//получение точки C
CPoint& CTriangle::GetPointC()
{
	return this->c;
}

//получение стороны А
double CTriangle::GetEdgeA()
{
	return abs((this->a.GetX() - this->b.GetX()) - (this->a.GetY() - this->b.GetY()));
}

//получение стороны B
double CTriangle::GetEdgeB()
{
	return abs((this->b.GetX() - this->c.GetX()) - (this->b.GetY() - this->c.GetY()));
}

//получение стороны C
double CTriangle::GetEdgeC()
{
	return abs((this->c.GetX() - this->a.GetX()) - (this->c.GetY() - this->a.GetY()));
}
