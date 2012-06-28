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
#ifndef ISILME_GRAPHICS_H
#define ISILME_GRAPHICS_H

#include "Definitions.h"
#include "GraphicsDefinition.h"

// Описание графической модели
class ISILME_API GraphicsDefinition 
{
public:
	virtual ~GraphicsDefinition() {}

	virtual void Parse(TiXmlElement* defElement);
	virtual GraphicsPtr Create() = 0;

	Vector2 Anchor;
protected:
	std::string mType;
};

// Класс описывает графику сущности
class ISILME_API Graphics
{
	friend class Entity;
	friend class FactoryManager;
	friend class EntityPalette;
public:
	Graphics(GraphicsDefinition* def = 0);
	virtual ~Graphics();

	/// Updates graphics
	virtual void Update(float elapsedTime);

	/// Визуализировать 
	virtual void Render(float x, float y, float angle);

	virtual void Reset() {};

	virtual void Attach(std::string tag, GraphicsPtr g);

	virtual void Remove(std::string tag);

	/// Сущность
	EntityPtr	GetEntity();

	/// Sets a scale.
	///
	/// @param	value	The value.
	void SetScale(float value);

	/// Gets the scale.
	///
	/// @return	The scale.
	float GetScale();

	/// Scales.
	///
	/// @param	scale	The scale.
	void Scale(float scale);

	/// Возвращает точку привязки графики к телу сущности
	Vector2	GetAnchor();

	/// Устанавливает точку привязки графики к телу
	void SetAnchor(Vector2 point);
protected:
	typedef std::map<std::string, GraphicsPtr> GraphicsMap;
	float mScale;
	EntityWPtr mEntity;
	GraphicsMap mAttached;
private:
	/// Точка привязки
	Vector2 mAnchor;
};

#endif