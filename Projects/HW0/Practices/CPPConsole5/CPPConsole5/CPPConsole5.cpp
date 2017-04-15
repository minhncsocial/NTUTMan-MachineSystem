// CPPConsole5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>

using namespace std;

CImage * cImg1 = new CImage();
HBITMAP * hBitmap;
LONG_PTR cImg2 = CreateCImage();

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "hello" << endl;

	//char * path = "D:/Test/fruits3.bmp";
	char * path = "D:/Test/50y_VUH1.bmp";
	bool _flag = false;

	//if (cImg1 != 0)
	//{
	//	_flag = cImg1->Load(path);
	//}

	//if (_flag) 
	//{
	//	hBitmap = (cImg1->GetBitmap());
	//}

	//if (cImg1 != 0)
	//{
	//	_flag = cImg1->Load(path);
	//}

	bool _flag1 = Load(cImg2, path);
	hBitmap = GetBitmap(cImg2);

	_getch();
	return 0;
}

