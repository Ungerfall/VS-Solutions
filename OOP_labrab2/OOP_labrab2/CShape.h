#pragma once

#ifndef CSHAPE_H
#define CSHAPE_H

#include <string>
#include "CPoint.h"
#include <iostream>

using namespace std;

//абстрактный класс фигура
class CShape
{
public:
	virtual double Square() = 0;	//вывести прощадь
	virtual void About() = 0;		//вывод информации о фигуре на экран
	virtual std::string Name() = 0;		//вывод названия фигуры
	bool operator < (CShape& opr);
	bool operator <= (CShape& opr);
	bool operator == (CShape& opr);
	bool operator != (CShape& opr);
	bool operator >= (CShape& opr);
	bool operator > (CShape& opr);
};

#endif