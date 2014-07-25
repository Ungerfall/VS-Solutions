#include "stdafx.h"
#include "MyMathFuncs.h"
#include <stdexcept>

using namespace std;

extern "C"
{
    double Add(double a, double b)
    {
        return a + b;
    }

    double Subtract(double a, double b)
    {
        return a - b;
    }

    double Multiply(double a, double b)
    {
        return a * b;
    }
}