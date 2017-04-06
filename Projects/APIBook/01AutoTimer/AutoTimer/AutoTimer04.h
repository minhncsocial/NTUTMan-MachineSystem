#ifndef AUTOTIMER04_H
#define AUTOTIMER04_H

#pragma once
#include <string>

class AutoTimer04
{
public:
	explicit AutoTimer04(const std::string &name);
	~AutoTimer04(void);

private:
	//Make this object be non-copyable
	AutoTimer04(const AutoTimer04 &);
	const AutoTimer04 &operator = (const AutoTimer04 &);

	class Impl;
	Impl *mImpl;
};

#endif