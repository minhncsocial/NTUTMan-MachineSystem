#include "ClassCaller01.h"


CClassCaller01::CClassCaller01(void)
{
}


CClassCaller01::~CClassCaller01(void)
{
}

CClass01* CreateClass01()
{
	return new CClass01();
}

void DisposeClass01(CClass01* a_pObject)
{
	if (a_pObject != nullptr)
	{
		delete a_pObject;
		a_pObject = nullptr;
	}
}

void showNotify(CClass01* a_pObject)
{
	if (a_pObject != nullptr)
	{
		a_pObject->showNotify();
	}
}

double sum(CClass01* a_pObject, double varX, double varY)
{
	if (a_pObject == nullptr)
	{
		throw invalid_argument("object can NOT be null");
	}
	return a_pObject->sum(varX, varY);
}

double testAdd(double a, double b)
{
	return a + b;
}

