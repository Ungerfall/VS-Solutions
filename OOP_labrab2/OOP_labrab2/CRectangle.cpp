#include "CRectangle.h"

const double pi = 3.14;

CRectangle::CRectangle()
	:a(CPoint(0, 3)), b(CPoint(0, 0)), c(CPoint(3, 0)) {}

//�����������
CRectangle::CRectangle(CPoint& a, CPoint& b, CPoint& c)
	:a(a), b(b), c(c) {}

std::string CRectangle::Name()
{
	return "�������������";
}

void CRectangle::About()
{
	cout << "\n������: " << "\t" << this->Name() << endl;
	cout << "����� ������:" << endl;
	cout << "a:\t\t" << this->GetEdgeA() << endl;
	cout << "b:\t\t" << this->GetEdgeB() << endl;
	cout << "�������:" << "\t" << this->Square();
}

double CRectangle::Square()
{
	double sqr;
	sqr = this->GetEdgeA() * this->GetEdgeB();
	return abs(sqr);
}

//��������� ������
void CRectangle::SetEdge(CPoint& a, CPoint& b)
{
	this->a = a;
	this->b = b;
}

//��������� ������� �
void CRectangle::SetA(CPoint& a)
{
	this->a = a;
}

//��������� ������� B
void CRectangle::SetB(CPoint& b)
{
	this->b = b;
}

//��������� ����� �
CPoint& CRectangle::GetPointA()
{
	return this->a;
}

//��������� ����� B
CPoint& CRectangle::GetPointB()
{
	return this->b;
}

//��������� ����� C
CPoint& CRectangle::GetPointC()
{
	return this->c;
}

//��������� ������� �
double CRectangle::GetEdgeA()
{
	return abs((this->a.GetX() - this->b.GetX()) - (this->a.GetY() - this->b.GetY()));
}

//��������� ������� B
double CRectangle::GetEdgeB()
{
	return abs((this->b.GetX() - this->c.GetX()) - (this->b.GetY() - this->c.GetY()));
}

//�������� �� �������������
bool CRectangle::IsRectangle(CRectangle& abc)
{
	return (abc.GetEdgeA() * abc.GetEdgeB() == abs((abc.a.GetX() - abc.c.GetX()) - (abc.a.GetY() - abc.c.GetY())));
}
