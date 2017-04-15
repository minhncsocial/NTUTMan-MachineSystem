#include "MathFuncDll.h"


//MathFuncDll::MathFuncDll(void)
//{
//}
//
//
//MathFuncDll::~MathFuncDll(void)
//{
//}

namespace MathFunc
{
	double Add(double a, double b)
	{
		return a+b;
	}
	double Subtract(double a, double b)
	{
		return a-b;
	}
	double Multiply(double a, double b)
	{
		return a*b;
	}
	double Divide(double a, double b)
	{
		if (b == 0)
			throw invalid_argument("b CAN NOT be zero!");
		return a/b;
	}
}