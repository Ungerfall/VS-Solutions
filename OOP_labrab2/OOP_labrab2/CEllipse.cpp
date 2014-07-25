#include "CEllipse.h"

using namespace std;

const double pi = 3.14;

CEllipse::CEllipse()
	:a(CPoint(0, 3)), b(CPoint(0, 0)), c(CPoint(3, 0)) {}

//конструктор
CEllipse::CEllipse(CPoint& a, CPoint& b, CPoint& c)
	:a(a), b(b), c(c) {}

std::string CEllipse::Name()
{
	return "Эллипс";
}

void CEllipse::About()
{
	cout << "\nФигура: " << "\t" << this->Name() << endl;
	cout << "Длины сторон:" << endl;
	cout << "a:\t\t" << this->GetEdgeA() << endl;
	cout << "b:\t\t" << this->GetEdgeB() << endl;
	cout << "Площадь:" << "\t" << this->Square();
}

double CEllipse::Square()
{
	double sqr;
	sqr = pi * this->GetEdgeA() * this->GetEdgeB();
	return abs(sqr);
}

//установка сторон
void CEllipse::SetEdge(CPoint& a, CPoint& b)
{
	this->a = a;
	this->b = b;
}

//установка стороны А
void CEllipse::SetA(CPoint& a)
{
	this->a = a;
}

//установка стороны B
void CEllipse::SetB(CPoint& b)
{
	this->b = b;
}

//получение точки А
CPoint& CEllipse::GetPointA()
{
	return this->a;
}

//получение точки B
CPoint& CEllipse::GetPointB()
{
	return this->b;
}

//получение точки C
CPoint& CEllipse::GetPointC()
{
	return this->c;
}

//получение стороны А
double CEllipse::GetEdgeA()
{
	return abs((this->a.GetX() - this->b.GetX()) - (this->a.GetY() - this->b.GetY()));
}

//получение стороны B
double CEllipse::GetEdgeB()
{
	return abs((this->b.GetX() - this->c.GetX()) - (this->b.GetY() - this->c.GetY()));
}

