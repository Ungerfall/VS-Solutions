#pragma once

#ifndef CSHAPE_H
#define CSHAPE_H

#include <string>
#include "CPoint.h"
#include <iostream>

using namespace std;

//����������� ����� ������
class CShape
{
public:
	virtual double Square() = 0;	//������� �������
	virtual void About() = 0;		//����� ���������� � ������ �� �����
	virtual std::string Name() = 0;		//����� �������� ������
	bool operator < (CShape& opr);
	bool operator <= (CShape& opr);
	bool operator == (CShape& opr);
	bool operator != (CShape& opr);
	bool operator >= (CShape& opr);
	bool operator > (CShape& opr);
};

#endif