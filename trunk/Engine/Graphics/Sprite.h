#ifndef ISILME_GRAPHICS_SPRITE_H
#define ISILME_GRAPHICS_SPRITE_H

#include "Definitions.h"
#include "Graphics.h"
#include <hge.h>

namespace graphics
{
	/// Описание спрайта
	class IsilmeExport SpriteDefinition : public GraphicsDefinition
	{
	public:
		HTEXTURE texture;
		float x;
		float y;
		float height;
		float width;

		SpriteDefinition();

		virtual ~SpriteDefinition();
		virtual void Parse(TiXmlElement* defElement);
		virtual GraphicsPtr Create();
	};



	/// @class Sprite
	/// Спрайтовая модель сущности
	class IsilmeExport Sprite : public Graphics
	{
	public:
		Sprite(SpriteDefinition* definition);
		virtual ~Sprite();

		/// Рисует спрайт 
		virtual void Render(float x, float y, float angle);

		virtual void Update(float elapsedTime);

		virtual void Reset();
	private:
		/// HGE-спрайт
		hgeSprite* mSprite;
	};
};
#endif
