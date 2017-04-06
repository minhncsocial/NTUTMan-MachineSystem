#include "RendererFactory.h"

RendererFactory::CallbackMap RendererFactory::mRenderers;

void RendererFactory::RegisterRenderer(const std::string &type, CreateCallback cb)
{
	mRenderers[type] = cb;
}
void RendererFactory::UnregisterRenderer(const std::string &type)
{
	mRenderers.erase(type);
}

IRenderer *RendererFactory::CreateRenderer(const std::string &type)
{
	CallbackMap::iterator it = mRenderers.find(type);
	if (it != mRenderers.end())
	{
		return (it->second)();
	}
	return NULL;
}
