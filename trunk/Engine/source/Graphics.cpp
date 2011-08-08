#include "Isilme.h"

Graphics::Graphics()
{
}

Graphics::~Graphics()
{
}

EntityPtr Graphics::GetEntity()
{
	return mEntity.lock();
}

void Graphics::Render(float x, float y, float angle)
{
	for (GraphicsMap::iterator it = mAttached.begin(); it != mAttached.end(); ++it)
		it->second->Render(x, y, angle);
}

void Graphics::Update(float elapsedTime)
{
	for (GraphicsMap::iterator it = mAttached.begin(); it != mAttached.end(); ++it)
		it->second->Update(elapsedTime);
}

void Graphics::Attach(std::string tag, GraphicsPtr g)
{
	mAttached[tag] = g;
}

void Graphics::Remove(std::string tag)
{
	GraphicsMap::iterator it = mAttached.find(tag);
	if (it != mAttached.end())
		mAttached.erase(it);
}
