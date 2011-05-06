#include "Isilme.h"

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
	}

	Sprite::Sprite(SpriteDefinition* definition)
	{
		mSprite = new hgeSprite(definition->texture, definition->x, definition->y, definition->width, definition->height);
	}

	Sprite::~Sprite()
	{
		delete mSprite;
	}

	void  Sprite::Render(float x, float y, float angle)
	{
		float width = mSprite->GetWidth() / 2.0f;
		float height = mSprite->GetHeight() / 2.0f;
		x -= (width*cos(angle) - height*sin(angle));
		y -= (width*sin(angle) + height*cos(angle));

		mSprite->RenderEx(x, y, angle);
	}

	void	Sprite::Update(float elapsedTime)
	{
	}

	GraphicsPtr SpriteDefinition::Create()
	{
		return GraphicsPtr(new Sprite(this));
	}
};