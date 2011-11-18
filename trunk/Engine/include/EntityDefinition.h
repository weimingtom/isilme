﻿#ifndef ENTITY_DEFINITION
#define ENTITY_DEFINITION

#include <string>
#include <map>
#include "Definitions.h"

/// Класс определения сущности
/// Фабрика использует эти определения для создания сущностей.
/// Создаются при загрузке XML-файла определений
class IsilmeExport EntityDefinition
{
	friend class FactoryManager;
public:
	EntityDefinition(BodyDef* body, GraphicsDefPtr graphics, BehaviourDefPtr behaviour);
	virtual ~EntityDefinition();

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
private:
	BodyDef*			mBody;
	GraphicsDefPtr		mGraphics;
	BehaviourDefPtr		mBehaviour;
	std::string			mType;
};

typedef std::map<std::string, EntityDefPtr> EntityPalette;
#endif