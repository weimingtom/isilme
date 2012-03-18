#ifndef ISILME_GRAPHICS_SPRITE_H
#define ISILME_GRAPHICS_SPRITE_H

#include "Definitions.h"
#include "Core/Graphics.h"
#include <hge.h>

namespace graphics
{
	/// Описание спрайта
	class ISILME_API SpriteDefinition : public GraphicsDefinition
	{
	public:
		HTEXTURE texture;
		float x;
		float y;
		float height;
		float width;
		Vector2 MetricSize;

		SpriteDefinition();

		virtual ~SpriteDefinition();
		virtual void Parse(TiXmlElement* defElement);
		virtual GraphicsPtr Create();
	};



	/// @class Sprite
	/// Спрайтовая модель сущности
	class ISILME_API Sprite : public Graphics
	{
	public:
		Sprite(SpriteDefinition* definition);
		virtual ~Sprite();

		/// Рисует спрайт 
		virtual void Render(float x, float y, float angle);

		virtual void Update(float elapsedTime);

		virtual void Reset();

		/// Возвращает ширину спрайта в метрах
		float GetMetricWidth();

		/// Возвращает высоту спрайта в метрах
		float GetMetricHeight();
	private:
		/// HGE-спрайт
		hgeSprite* mSprite;

		/// Высота спрайта в метрах
		float mHeight;

		/// Ширина спрайта в метрах
		float mWidth;
	};
};
#endif
