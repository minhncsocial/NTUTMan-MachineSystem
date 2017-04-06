#ifndef AUTOTIMER02_H
#define AUTOTIMER02_H

#pragma once
#include <string>

class AutoTimer02
{
public:
	explicit AutoTimer02(const std::string &name);
	~AutoTimer02(void);

private:
	class Impl;
	Impl *mImpl;
};

#endif