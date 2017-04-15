#ifndef LLWEB_H
#define LLWEB_H

#pragma once

#include <string>

class LLWeb
{
public:
	//LLWeb(void);
	//~LLWeb(void);
	static void InitClass();
	static void LoadURL(const std::string& url);
	static void LoadURLInternal(const std::string& url);
	static void LoadURLExternal(const std::string& url);
	static std::string EscapeURL(const std::string& url);
};

#endif