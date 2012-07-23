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
//#include "IsilmePCH.h"
#include "Animation.h"
#include "Core/ResourceManager.h"

namespace graphics
{	
	Animation::Animation(AnimationDefinition* def) : 
		Graphics(def)
	{
		mAnimation = new hgeAnimation(def->texture, def->frames, def->fps, def->x, def->y, def->width, def->height);
		mAnimation->Play();
		mAnimation->SetMode(def->loop ? HGEANIM_LOOP : HGEANIM_NOLOOP);
	}

	Animation::~Animation()
	{
		delete mAnimation;
	}

	void Animation::Reset()
	{
		mAnimation->Stop();
		mAnimation->Play();
	}

	void Animation::Render(float x, float y, float angle)
	{
		float width = mAnimation->GetWidth() * GetScale() / 2.0f;
		float height = mAnimation->GetHeight() * GetScale() / 2.0f;
		x -= (width*cos(angle) - height*sin(angle));
		y -= (width*sin(angle) + height*cos(angle));

		mAnimation->RenderEx(x, y, angle, GetScale(), GetScale());
	}

	void Animation::Update(float elapsedTime)
	{
		mAnimation->Update(elapsedTime);
	}

	void AnimationDefinition::Parse(TiXmlElement* defElement)
	{
		GraphicsDefinition::Parse(defElement);

		const char* textureFile = defElement->GetText();
		texture = Engine::GetSingleton()->GetResourceManager()->GetTexture(textureFile);
		x = 0.0f;
		y = 0.0f;
		width = 0.0f;
		height = 0.0f;
		frames = 1;
		loop = true;
		fps = 10.0;
		int isLoop = 1;

		defElement->QueryFloatAttribute("X", &x);
		defElement->QueryFloatAttribute("Y", &y);
		defElement->QueryFloatAttribute("Width", &width);
		defElement->QueryFloatAttribute("Height", &height);
		defElement->QueryIntAttribute("Frames", &frames);
		defElement->QueryFloatAttribute("FPS", &fps);
		defElement->QueryIntAttribute("Loop", &isLoop);
		loop = (isLoop != 0);
	}

	AnimationDefinition::AnimationDefinition()
	{
	}

	AnimationDefinition::~AnimationDefinition()
	{
	}

	GraphicsPtr	AnimationDefinition::Create()
	{
		return GraphicsPtr(new Animation(this));
	}
};