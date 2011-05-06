#ifndef LEVEL_LOADER_H
#define LEVEL_LOADER_H

#include "Definitions.h"
#include <tinyxml.h>
#include <string>
#include <map>
#include <list>
#include <vector>

class IsilmeExport ActionDefinition
{
public:
	ActionDefinition();
	virtual ~ActionDefinition();

	virtual void Parse(TiXmlElement* actionElement) = 0;
};

class IsilmeExport EntityData
{
public:
	float x;
	float y;
	float angle;
	float scale;
	std::string type;
	std::string name;
};


class IsilmeExport GroupData
{
public:
	float x;
	float y;
	std::map<std::string, EntityData> entities;
	std::vector<JointDefPtr> joints;
};

class IsilmeExport LevelLoader
{
public:
	LevelLoader();
	virtual ~LevelLoader();

	void	LoadLevel(LevelPtr level, std::string fileName);

	void	SaveLevel(LevelPtr level, std::string fileName);

	static LevelLoader*	GetSingleton();

protected:
	typedef std::map<std::string, GroupData> GroupDataMap;
	GroupDataMap	mGroups;
	LevelPtr			mLevel;
	static LevelLoader* mInstance;

	/// Считывает описание камеры и создает камеру на уровне
	void	ParseCamera(LevelPtr level, TiXmlElement* rootElement);

	void	ParseWorld(LevelPtr level, TiXmlElement*	rootElement);

	/// Считывает описание групп объектов
	void	ParseGroups(TiXmlElement* rootElement);

	/// Считывает и создает слои
	void	ParseLayers(LevelPtr level, TiXmlElement* rootElement);

	/// Считывание и создание связей
	void	ParseJoints(LevelPtr level, TiXmlElement* rootElement);
	EntityData	ParseEntity(TiXmlElement* entityElement);
	GroupData	ParseGroup(TiXmlElement* groupElement);

	/// Размещение сущности на уровне
	void	PlaceEntity(LevelPtr level, LayerPtr layer, EntityData& data);

	/// Размещение группы сущностей на уровне
	void	PlaceGroup(LevelPtr level, LayerPtr layer, GroupData& data);

	void	ParseScripts(TiXmlElement* rootElement);
};
#endif