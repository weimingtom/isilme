#include "IsilmePCH.h"

Graphics::Graphics(GraphicsDefinition* def) 
{
	mAnchor.Set(0.0f, 0.0f);
	if (def)
	{
		mAnchor = def->Anchor;
		mScale = 1.0f;
	}
}

Graphics::~Graphics()
{
}

EntityPtr Graphics::GetEntity()
{
	return mEntity.lock();
}

void Graphics::Render( float x, float y, float angle)
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

void Graphics::SetScale(float value)
{
	mScale = value;
}

float Graphics::GetScale()
{
	return mScale;
}

void Graphics::Scale(float value)
{
	SetScale(mScale * value);
}

void Graphics::SetAnchor( Vector2 point )
{
	mAnchor = point;
}

Vector2 Graphics::GetAnchor()
{
	return mAnchor;
}

void GraphicsDefinition::Parse( TiXmlElement* defElement )
{
	if (!defElement)
		return;

	if (defElement->Attribute("Anchor"))
	{
		char buf[100];
		sscanf(buf, "%f, %f", &Anchor.x, &Anchor.y);
	}
}
