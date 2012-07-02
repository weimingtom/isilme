//  Copyright (C) 2010-2012 VSTU
//
//	This file is part of Isilme SDK.
//
//		Isilme SDK is free software: you can redistribute it and/or modify
//		it under the terms of the GNU Lesser General Public License as published by
//		the Free Software Foundation, either version 3 of the License, or
//		(at your option) any later version.
//
//		Isilme SDK is distributed in the hope that it will be useful,
//		but WITHOUT ANY WARRANTY; without even the implied warranty of
//		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//		GNU Lesser General Public License for more details.
//
//		You should have received a copy of the GNU Lesser General Public License
//		along with Isilme SDK.  If not, see <http://www.gnu.org/licenses/>.
//
//	Этот файл — часть Isilme SDK.
//
//		Isilme SDK - свободная программа: вы можете перераспространять ее и/или
//		изменять ее на условиях Меньшей стандартной общественной лицензии GNU в том виде,
//		в каком она была опубликована Фондом свободного программного обеспечения;
//		либо версии 3 лицензии, либо (по вашему выбору) любой более поздней
//		версии.
//
//		Isilme SDK распространяется в надежде, что она будет полезной,
//		но БЕЗО ВСЯКИХ ГАРАНТИЙ; даже без неявной гарантии ТОВАРНОГО ВИДА
//		или ПРИГОДНОСТИ ДЛЯ ОПРЕДЕЛЕННЫХ ЦЕЛЕЙ. Подробнее см. в Меньшей стандартной
//		общественной лицензии GNU.
//
//		Вы должны были получить копию Меньшей стандартной общественной лицензии GNU
//		вместе с этой программой. Если это не так, см.
//		<http://www.gnu.org/licenses/>.
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
