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
#include "EntityPalette.h"
#include "Core/EntityDefinition.h"
#include "Core/Behaviour.h"
#include "../Core/Engine.h"
#include "../Core/ResourceManager.h"

std::string itoa (const int value,
      const unsigned int base=10,
      const bool printf_style=true)
{
    const char *base_key = "0123456789abcdef";
    std::string s = "0";
    unsigned int v = value;
    
    if (base >= 2 && base <= 16 && value)
    {
        s = "";
        if (value < 0 && (base == 10 || !printf_style))
            v = -value;
        
        while (v != 0)
        {
            s.insert (s.begin (), 1, base_key[v % base]);
            v /= base;
        }
    }
    
    if (value < 0 && (base == 10 || !printf_style))
        s.insert (s.begin (), 1, '-');
    return s;
}

EntityPalette::EntityPalette()
{

}

EntityPalette::~EntityPalette()
{

}

EntityPalette::EntityDefMap* EntityPalette::GetData() 
{
	return &mPalette;
}

EntityDefPtr EntityPalette::GetDefinition( std::string type ) 
{
	return mPalette[type];
}

void EntityPalette::Add( EntityDefPtr def )
{
	mPalette[def->GetType()] = def;
}

void EntityPalette::AddDefinition( EntityDefPtr def )
{
	mPalette[def->GetType()] = def;
}

void EntityPalette::Destroy( std::string id )
{
	EntityMap::iterator it = mEntites.find(id);
	if (it != mEntites.end())
	{
		mEntites.erase(it);
		it->second->Remove();
	}
}

void EntityPalette::Destroy( EntityPtr entity )
{
	entity->Remove();
	EntityMap::iterator it = mEntites.find(entity->GetName());
	if (it != mEntites.end())
		mEntites.erase(it);
}

EntityPtr EntityPalette::Create( std::string type, std::string id )
{
	EntityDefPtr def = GetDefinition(type);
	if (!def)
		return EntityPtr();

	Body* body;
	if (def->GetBodyDefinition()->Type == BodyDef::SimpleBody)
	{ 
		body = new SimpleBody();
	}
	else if (def->GetBodyDefinition()->Type == BodyDef::Box2DBody)
	{
		body = new Box2DBody(def->GetBodyDefinition());
	}

	GraphicsPtr graphics	= def->GetGraphicsDefinition()->Create();
	BehaviourPtr behaviour	= def->GetBehaviourDefinition()->Create();

	EntityPtr entity(new Entity());
	entity->mGraphics = graphics;
	entity->mBehaviour = behaviour;
	entity->mBody = body;

	graphics->mEntity = entity;
	behaviour->mActor = entity;
	body->SetEntity(entity.get());

	if (id == "")
	{
		std::string prefix = "GameObject_";
		int n = 0;
		while (mEntites.find(prefix + itoa(n, 16)) != mEntites.end())
			++n;
		id = prefix + itoa(n, 16);
	}

	entity->mName = id;
	entity->mType = def->GetType();

	mEntites[id] = entity;

	return entity;
}

EntityPtr EntityPalette::GetEntity( std::string name )
{
	return mEntites[name];
}
