#include "StdAfx.h"
#include <iostream>
#include "RendererFactory.h"

using namespace std;

class OpenGLRenderer: public IRenderer
{
public:
	~OpenGLRenderer() {}
	bool LoadScene(const std::string& filename) { return true;}
	void SetViewportSize(int w, int h) {};
	void Render() { cout << "OpenGL Render" << endl;}
};

class DirectXRenderer: public IRenderer
{
public:
	~DirectXRenderer() {}
	bool LoadScene(const std::string& filename) { return true;}
	void SetViewportSize(int w, int h) {};
	void Render() { cout << "DirectX Render" << endl;}
};

class MesaRenderer: public IRenderer
{
public:
	~MesaRenderer() {}
	bool LoadScene(const std::string& filename) { return true;}
	void SetViewportSize(int w, int h) {};
	void Render() { cout << "Mesa Render" << endl;}
};

IRenderer * RendererFactory::CreateRenderer(const std::string &type)
{
	if (type == "opengl") return new OpenGLRenderer;
	if (type == "directx") return new DirectXRenderer;
	if (type == "mesa") return new MesaRenderer;

	return NULL;
};
