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
#ifndef COLLISIONS_H
#define COLLISIONS_H

#include <Box2D/Box2D.h>
#include <string>
#include <map>

class ISILME_API DestructionListener : public b2DestructionListener
{
public:
	DestructionListener();
	virtual ~DestructionListener();
	virtual void SayGoodbye(b2Fixture* fixtuure);
	virtual void SayGoodbye(b2Joint* joint);
protected:
};

class ISILME_API ContactListener : public b2ContactListener
{
public:
	ContactListener();
	virtual ~ContactListener();
	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldMainfold);
protected:
};

class ISILME_API ContactFilter : public b2ContactFilter
{
public:
	ContactFilter();
	virtual ~ContactFilter();
	virtual bool ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB);
protected:
};

// Класс физического движка
class ISILME_API Box2DEngine
{
public:
	b2World* CreateWorld();
	static Box2DEngine* GetSingleton();
protected:
	Box2DEngine();
	virtual ~Box2DEngine();

	static Box2DEngine*	mInstance;
};

#endif