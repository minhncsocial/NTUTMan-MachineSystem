#include "header.h"
#include <stdio.h>
#include <conio.h>

void main()
{
	myClass sumTwoClass(10, 5);
	double result = sumTwoClass.sumX_Y();
	printf("%f", result);
	_getch();
}