#ifndef AUTOTIMER01_H
#define AUTOTIMER01_H

#pragma once
#include <string>
#include <Windows.h>

class AutoTimer01
{
public:
	explicit AutoTimer01(const std::string &name);
	~AutoTimer01(void);

private:
	double GetElapsed() const;

	std::string mName;
	DWORD mStartTime;
};

#endif