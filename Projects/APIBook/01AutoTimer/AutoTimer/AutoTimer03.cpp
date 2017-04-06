#include "AutoTimer03.h"
#include <iostream>
#include <Windows.h>

class AutoTimer03::Impl
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

AutoTimer03::AutoTimer03(const std::string &name) : mImpl(new AutoTimer03::Impl())
{
	mImpl->mStartTime = GetTickCount();
}


AutoTimer03::~AutoTimer03(void)
{
	std::cout << mImpl->mName << ": took" << mImpl->GetElapsed() << " secs" << std::endl;
	delete mImpl;
	mImpl = NULL;
}
