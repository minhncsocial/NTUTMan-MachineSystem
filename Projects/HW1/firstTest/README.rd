How to create DLL lib to use???
1. create DLL lib (SimpleDLL project)
2. try to use that DLL lib (ConsoleApplication4 project)

How to create project:
1. New -> create a Win32 Project name:SimpleDLL -> select DLL, select empty project -> OK
2. Add new file SimpleH.h
3. Add new file SimpleCPP.cpp
4. in the SimpleH.h, code:
namespace nmspace 
{
	class myclass
	{
	public:
		static _declspec(dllexport) void Crap();
	};
}
5. in the SimpleCPP, code:
#include <iostream>
using namespace std;
#include "SimpleH.h"

namespace nmspace
{
	void myclass::Crap()
	{
		cout << "I'm called within a crappy DLL";
	}
}
6. Select BuilDLL (not build project, solution, ...)

How to use DLL:
1. New -> create a Win32 Project name:SimpleDLL -> select empty project
2. Add new file main.cpp
3. in the main.cpp, code:
#include <iostream>
#include <stdio.h>
#include <conio.h>

#include "SimpleH.h"

using namespace std;
using namespace nmspace;

int main()
{
	printf("haha \n");
	myclass::Crap();
	_getch();
	return 0;
}
4. re-config project's configuration: Configuration Properties -> Linker -> Input -> Additional Dependencies -> new: type SimpleDLL.lib
-> OK
5. Build project to see result
