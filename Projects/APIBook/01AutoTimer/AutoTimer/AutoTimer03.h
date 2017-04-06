#ifndef AUTOTIMER03_H
#define AUTOTIMER03_H

#pragma once
#include <string>
class AutoTimer03
{
public:
	explicit AutoTimer03(const std::string &name);
	~AutoTimer03(void);
	class Impl;

private:
	Impl *mImpl;
};

#endif