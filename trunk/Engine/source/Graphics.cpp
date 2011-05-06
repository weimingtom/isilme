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
}

void Graphics::Update(float elapsedTime)
{
}
