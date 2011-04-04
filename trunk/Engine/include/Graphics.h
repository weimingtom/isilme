#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <hgesprite.h>
#include <hgeanim.h>
#include <tinyXML.h>
#include <string>
#include <map>
#include "Definitions.h"
#include "Engine/Loading/GraphicsDefinition.h"

// Описание графической модели
class IsilmeExport GraphicsDefinition 
{
public:
	virtual ~GraphicsDefinition() {}

	virtual void Parse(TiXmlElement* defElement) = 0;
	virtual GraphicsPtr Create() = 0;
protected:
	std::string mType;
};

// Класс описывает графику сущности
class IsilmeExport Graphics
{
	friend class Entity;
public:
	Graphics();
	virtual ~Graphics();

	/// Обновить графику
	virtual void Update(float elapsedTime);

	/// Визуализировать 
	virtual void Render(float x, float y, float angle);

	/// Сущность
	EntityPtr	GetEntity();
protected:
	EntityWPtr mEntity;
};

#endif