// CPPConsole02.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
//#include "Image.h"
//#include "mImage.h"
//#include "IProcessD.h"

using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	cout << "HELLO" << endl;

	CImage * cImg = new CImage();
	CImage * hBitmap;
	HBITMAP * temp;
	char * path = "D:/Test/fruits3.bmp";
	bool _flag = false;

	if (cImg != 0)
	{
		_flag = cImg->LoadBMP(path);
	}

	if (_flag) 
	{
		temp = (cImg->GetBitmap());
	}

	int _height = cImg->GetHeight();
	int _width = cImg->GetWidth();



	_getch();
	return 0;
}

