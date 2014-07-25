#include "CRectangle.h"

const double pi = 3.14;

CRectangle::CRectangle()
	:a(CPoint(0, 3)), b(CPoint(0, 0)), c(CPoint(3, 0)) {}

//конструктор
CRectangle::CRectangle(CPoint& a, CPoint& b, CPoint& c)
	:a(a), b(b), c(c) {}

std::string CRectangle::Name()
{
	return "Прямоугольник";
}

void CRectangle::About()
{
	cout << "\nФигура: " << "\t" << this->Name() << endl;
	cout << "Длины сторон:" << endl;
	cout << "a:\t\t" << this->GetEdgeA() << endl;
	cout << "b:\t\t" << this->GetEdgeB() << endl;
	cout << "Площадь:" << "\t" << this->Square();
}

double CRectangle::Square()
{
	double sqr;
	sqr = this->GetEdgeA() * this->GetEdgeB();
	return abs(sqr);
}

//установка сторон
void CRectangle::SetEdge(CPoint& a, CPoint& b)
{
	this->a = a;
	this->b = b;
}

//установка стороны А
void CRectangle::SetA(CPoint& a)
{
	this->a = a;
}

//установка стороны B
void CRectangle::SetB(CPoint& b)
{
	this->b = b;
}

//получение точки А
CPoint& CRectangle::GetPointA()
{
	return this->a;
}

//получение точки B
CPoint& CRectangle::GetPointB()
{
	return this->b;
}

//получение точки C
CPoint& CRectangle::GetPointC()
{
	return this->c;
}

//получение стороны А
double CRectangle::GetEdgeA()
{
	return abs((this->a.GetX() - this->b.GetX()) - (this->a.GetY() - this->b.GetY()));
}

//получение стороны B
double CRectangle::GetEdgeB()
{
	return abs((this->b.GetX() - this->c.GetX()) - (this->b.GetY() - this->c.GetY()));
}

//проверка на прямоугольник
bool CRectangle::IsRectangle(CRectangle& abc)
{
	return (abc.GetEdgeA() * abc.GetEdgeB() == abs((abc.a.GetX() - abc.c.GetX()) - (abc.a.GetY() - abc.c.GetY())));
}
