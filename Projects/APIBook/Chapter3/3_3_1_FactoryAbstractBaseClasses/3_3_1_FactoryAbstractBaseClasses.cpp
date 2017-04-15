// 3_3_1_FactoryAbstractBaseClasses.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include "RendererFactory.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	RendererFactory *f = new RendererFactory;

	IRenderer *opengl = f->CreateRenderer("directx");
	opengl->Render();
	delete opengl;


	_getch();
	return 0;
}

