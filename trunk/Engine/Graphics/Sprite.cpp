//  Copyright (C) 2010-2012 Alexander Alimov
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
#include "IsilmePCH.h"
#include "Sprite.h"
#include "Core/ResourceManager.h"

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