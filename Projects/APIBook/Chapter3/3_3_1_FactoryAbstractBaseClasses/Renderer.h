#ifndef RENDERER_H
#define RENDERER_H

#pragma once

#include <string>

//class Renderer
//{
//public:
//	Renderer(void);
//	~Renderer(void);
//};

class IRenderer
{
public:
	//IRenderer(void);
	virtual ~IRenderer(void) {}
	virtual bool LoadScene(const std::string& filename) = 0;
	virtual void SetViewportSize(int w, int h) = 0;
	virtual void Render() = 0;
};

#endif