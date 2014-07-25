#include "CEllipse.h"

using namespace std;

const double pi = 3.14;

CEllipse::CEllipse()
	:a(CPoint(0, 3)), b(CPoint(0, 0)), c(CPoint(3, 0)) {}

//�����������
CEllipse::CEllipse(CPoint& a, CPoint& b, CPoint& c)
	:a(a), b(b), c(c) {}

std::string CEllipse::Name()
{
	return "������";
}

void CEllipse::About()
{
	cout << "\n������: " << "\t" << this->Name() << endl;
	cout << "����� ������:" << endl;
	cout << "a:\t\t" << this->GetEdgeA() << endl;
	cout << "b:\t\t" << this->GetEdgeB() << endl;
	cout << "�������:" << "\t" << this->Square();
}

double CEllipse::Square()
{
	double sqr;
	sqr = pi * this->GetEdgeA() * this->GetEdgeB();
	return abs(sqr);
}

//��������� ������
void CEllipse::SetEdge(CPoint& a, CPoint& b)
{
	this->a = a;
	this->b = b;
}

//��������� ������� �
void CEllipse::SetA(CPoint& a)
{
	this->a = a;
}

//��������� ������� B
void CEllipse::SetB(CPoint& b)
{
	this->b = b;
}

//��������� ����� �
CPoint& CEllipse::GetPointA()
{
	return this->a;
}

//��������� ����� B
CPoint& CEllipse::GetPointB()
{
	return this->b;
}

//��������� ����� C
CPoint& CEllipse::GetPointC()
{
	return this->c;
}

//��������� ������� �
double CEllipse::GetEdgeA()
{
	return abs((this->a.GetX() - this->b.GetX()) - (this->a.GetY() - this->b.GetY()));
}

//��������� ������� B
double CEllipse::GetEdgeB()
{
	return abs((this->b.GetX() - this->c.GetX()) - (this->b.GetY() - this->c.GetY()));
}

