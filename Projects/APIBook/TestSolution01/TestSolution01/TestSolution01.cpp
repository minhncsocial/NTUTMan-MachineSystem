// TestSolution01.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <boost\shared_ptr.hpp>

#include "coord2D.h"

using namespace std;

typedef boost::shared_ptr<class Myobject> MyObjectPtr;

int _tmain(int argc, _TCHAR* argv[])
{
	printf("hello\n");

	//2.4.3. coord2D lib
	Coord2D<float> vector(3.0, 5.0);
	cout <<"(" << vector.GetX() << ", " << vector.GetY() << ")" << endl;
	
	_getch();

	return 0;
}

