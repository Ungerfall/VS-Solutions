#include "CTriangle.h"

using namespace std;

CTriangle::CTriangle()
	:a(CPoint(0, 3)), b(CPoint(0, 0)), c(CPoint(3, 0)) {}

//�����������
CTriangle::CTriangle(CPoint& a, CPoint& b, CPoint& c)
	:a(a), b(b), c(c) {}

std::string CTriangle::Name()
{
	return "�����������";
}

void CTriangle::About()
{
	cout << "\n������: " << "\t" << this->Name() << endl;
	cout << "����� ������:" << endl;
	cout << "a:\t\t" << this->GetEdgeA() << endl;
	cout << "b:\t\t" << this->GetEdgeB() << endl;
	cout << "c:\t\t" << this->GetEdgeC() << endl;
	cout << "�������:" << "\t" << this->Square();
}

double CTriangle::Square()
{
	double sqr;
	sqr = 0.5 * ((this->b.GetX() - this->a.GetX()) * (this->c.GetY() - this->a.GetY()) - ((this->c.GetX() - this->a.GetX()) * (this->b.GetY() - this->a.GetY())));
	return abs(sqr);
}

//��������� ������
void CTriangle::SetEdge(CPoint& a, CPoint& b, CPoint& c)
{
	this->a = a;
	this->b = b;
	this->c = c;
}

//��������� ������� �
void CTriangle::SetA(CPoint& a)
{
	this->a = a;
}

//��������� ������� B
void CTriangle::SetB(CPoint& b)
{
	this->b = b;
}

//��������� ������� C
void CTriangle::SetC(CPoint& c)
{
	this->c = c;
}

//��������� ����� �
CPoint& CTriangle::GetPointA()
{
	return this->a;
}

//��������� ����� B
CPoint& CTriangle::GetPointB()
{
	return this->b;
}

//��������� ����� C
CPoint& CTriangle::GetPointC()
{
	return this->c;
}

//��������� ������� �
double CTriangle::GetEdgeA()
{
	return abs((this->a.GetX() - this->b.GetX()) - (this->a.GetY() - this->b.GetY()));
}

//��������� ������� B
double CTriangle::GetEdgeB()
{
	return abs((this->b.GetX() - this->c.GetX()) - (this->b.GetY() - this->c.GetY()));
}

//��������� ������� C
double CTriangle::GetEdgeC()
{
	return abs((this->c.GetX() - this->a.GetX()) - (this->c.GetY() - this->a.GetY()));
}
