#include "CShape.h"

bool CShape::operator < (CShape& opr)
{
	return (this->Square() < opr.Square());
}

bool CShape::operator <= (CShape& opr)
{
	return (this->Square() <= opr.Square());
}

bool CShape::operator == (CShape& opr)
{
	return (this->Square() == opr.Square());
}

bool CShape::operator != (CShape& opr)
{
	return !(this->Square() == opr.Square());
}

bool CShape::operator >= (CShape& opr)
{
	return (this->Square() >= opr.Square());
}

bool CShape::operator > (CShape& opr)
{
	return (this->Square() > opr.Square());
}