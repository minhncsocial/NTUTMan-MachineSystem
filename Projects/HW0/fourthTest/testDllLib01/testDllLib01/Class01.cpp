#include "Class01.h"
#include <iostream>
using namespace std;


CClass01::CClass01(void)
{
}


CClass01::~CClass01(void)
{
}

void CClass01::showNotify(void)
{
	std::cout << "asd asd " << std::endl;
}

double CClass01::sum(double varX, double varY)
{
	return varX + varY;
}