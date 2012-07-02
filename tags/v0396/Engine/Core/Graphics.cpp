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
