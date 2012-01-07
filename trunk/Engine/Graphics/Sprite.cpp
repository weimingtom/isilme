#include "IsilmePCH.h"
#include "Sprite.h"
#include "ResourceManager.h"

namespace graphics
{
	SpriteDefinition::SpriteDefinition()
	{
	}

	SpriteDefinition::~SpriteDefinition()
	{
	}

	void SpriteDefinition::Parse(TiXmlElement* defElement)
	{
		const char* textureFile = defElement->GetText();
		texture = Engine::GetSingleton()->GetResourceManager()->GetTexture(textureFile);
		x = 0.0f;
		y = 0.0f;
		width = 0.0f;
		height = 0.0f;


		defElement->QueryFloatAttribute("X", &x);
		defElement->QueryFloatAttribute("Y", &y);
		defElement->QueryFloatAttribute("Width", &width);
		defElement->QueryFloatAttribute("Height", &height);

		MetricSize.Set(width / 64.0f, height / 64.0f);
	}

	Sprite::Sprite(SpriteDefinition* definition) : 
		Graphics(definition)
	{
		mSprite = new hgeSprite(definition->texture, definition->x, definition->y, definition->width, definition->height);

		mHeight = definition->MetricSize.y;
		mWidth = definition->MetricSize.x;
	}

	Sprite::~Sprite()
	{
		delete mSprite;
	}

	void  Sprite::Reset()
	{
		
	}

	void  Sprite::Render(float x, float y, float angle)
	{
		float width = /*mWidth * GetScale() / 2.0f;*/ mSprite->GetWidth() * GetScale() / 2.0f;
		float height = /*mHeight * GetScale() / 2.0f;*/ mSprite->GetHeight() * GetScale() / 2.0f;
		x -= (width*cos(angle) - height*sin(angle));
		y -= (width*sin(angle) + height*cos(angle));

		mSprite->RenderEx(x, y, angle, GetScale(), GetScale());
	}

	void	Sprite::Update(float elapsedTime)
	{
	}

	float Sprite::GetMetricWidth()
	{
		return mWidth;
	}

	float Sprite::GetMetricHeight()
	{
		return mHeight;
	}

	GraphicsPtr SpriteDefinition::Create()
	{
		return GraphicsPtr(new Sprite(this));
	}
};