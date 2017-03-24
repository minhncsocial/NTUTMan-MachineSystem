// MyDLL.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "MyDLL.h"


// This is an example of an exported variable
MYDLL_API int nMyDLL=0;

// This is an example of an exported function.
MYDLL_API int fnMyDLL(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see MyDLL.h for the class definition
CMyDLL::CMyDLL()
{
	return;
}
