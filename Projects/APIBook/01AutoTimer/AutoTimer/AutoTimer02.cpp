#include "AutoTimer02.h"
#include <iostream>
#include <Windows.h>

class AutoTimer02::Impl
{
public:
	double GetElapsed() const
	{
		return (GetTickCount() - mStartTime)/1e3;
	}
	
	std::string mName;
	DWORD mStartTime;

private:

};

AutoTimer02::AutoTimer02(const std::string &name) : mImpl(new AutoTimer02::Impl())
{
	mImpl->mStartTime = GetTickCount();
}


AutoTimer02::~AutoTimer02(void)
{
	std::cout << mImpl->mName << ": took" << mImpl->GetElapsed() << " secs" << std::endl;
	delete mImpl;
	mImpl = NULL;
}
