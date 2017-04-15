// 3_3_3_FactoryExtensible.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include "RendererFactory.h"

using namespace std;

class UserRenderer : public IRenderer
{
public:
	~UserRenderer() {}
	bool LoadScene(const std::string &filename) { return true; }
	void SetViewportSize(int w, int h) {}
	void SetCameraPosition(double x, double y, double z) {}
	void SetLookAt(double x, double y, double z) {}
	void Render() { std::cout << "User Render" << std::endl; }
	static IRenderer *Create() { return new UserRenderer(); }
};

/// An OpenGL-based 3D renderer
class OpenGLRenderer : public IRenderer
{
public:
	~OpenGLRenderer() {}
	bool LoadScene(const std::string &filename) { return true; }
	void SetViewportSize(int w, int h) {}
	void SetCameraPos(double x, double y, double z) {}
	void SetLookAt(double x, double y, double z) {}
	void Render() { cout << "OpenGL Render" << endl; }
	static IRenderer *Create() { return new OpenGLRenderer; }
};

/// An OpenGL-based 3D renderer
class DirectXRenderer : public IRenderer
{
public:
	~DirectXRenderer() {}
	bool LoadScene(const std::string &filename) { return true; }
	void SetViewportSize(int w, int h) {}
	void SetCameraPos(double x, double y, double z) {}
	void SetLookAt(double x, double y, double z) {}
	void Render() { cout << "DirectX Render" << endl; }
	static IRenderer *Create() { return new DirectXRenderer(); }
};

int _tmain(int argc, _TCHAR* argv[])
{
	// register a new renderer
	RendererFactory::RegisterRenderer("user", UserRenderer::Create);
	RendererFactory::RegisterRenderer("opengl", OpenGLRenderer::Create);
	RendererFactory::RegisterRenderer("opengl", DirectXRenderer::Create);

	// create an instance of our new renderer
	IRenderer *r = RendererFactory::CreateRenderer("user");
	r->Render();
	delete r;

	_getch();
	return 0;
}

