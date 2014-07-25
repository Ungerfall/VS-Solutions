#pragma once

#ifdef MATHFUNCSDLL_EXPORTS
#define MATHFUNCSDLL_API __declspec(dllexport) 
#else
#define MATHFUNCSDLL_API __declspec(dllimport) 
#endif

extern "C"
{
	MATHFUNCSDLL_API double Add(double a, double b); 

	MATHFUNCSDLL_API double Subtract(double a, double b); 

	MATHFUNCSDLL_API double Multiply(double a, double b); 
}

