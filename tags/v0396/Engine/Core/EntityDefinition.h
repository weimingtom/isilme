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
#ifndef ENTITY_DEFINITION
#define ENTITY_DEFINITION

#include <string>
#include <map>
#include "Definitions.h"

/// Класс определения сущности
/// Фабрика использует эти определения для создания сущностей.
/// Создаются при загрузке XML-файла определений
class ISILME_API EntityDefinition
{
	friend class FactoryManager;
public:
	EntityDefinition(BodyDef* body, GraphicsDefPtr graphics, BehaviourDefPtr behaviour);
	virtual ~EntityDefinition();

	/// Creates entity
	//EntityPtr Create();

	/// Возвращает определение для физической модели сущности
	BodyDef*				GetBodyDefinition();

	/// Возвращает определение для графической модели сущности
	GraphicsDefPtr	GetGraphicsDefinition();

	/// Возвращает определение для поведения сущности
	BehaviourDefPtr	GetBehaviourDefinition();

	/// Gets the type.
	///
	/// @return	The type.
	std::string		GetType();

	std::string			mType;
private:
	BodyDef*			mBody;
	GraphicsDefPtr		mGraphics;
	BehaviourDefPtr		mBehaviour;
};

#endif