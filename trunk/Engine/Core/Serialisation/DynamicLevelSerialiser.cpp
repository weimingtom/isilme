#include "IsilmePCH.h"
#include "DynamicLevelSerialiser.h"
#include "LevelSerialiser.h"
#include "Layer.h"
#include "Level.h"
#include "Entity.h"
#include "Behaviour.h"
#include "FactoryManager.h"
#include "../MasterFile.h"

namespace serialisation
{
	DynamicLevelSerialiser::DynamicLevelSerialiser()
	{
	
	}

	DynamicLevelSerialiser::~DynamicLevelSerialiser()
	{
	
	}

	void DynamicLevelSerialiser::Serialise(LevelPtr level, std::string fileName)
	{

	}

	TiXmlElement* DynamicLevelSerialiser::Serialise( LevelPtr level )
	{
		TiXmlElement* levelElement = new TiXmlElement("Level");

		for (int i = 0; i < level->GetLayersCount(); ++i)
		{
			levelElement->InsertEndChild(*SerialiseLayer(level->GetLayer(i)));
		}
		return levelElement;
	}

	TiXmlElement* DynamicLevelSerialiser::SerialiseEntity( EntityPtr entity )
	{
		TiXmlElement* element = new TiXmlElement("Entity");

		// Сохраняем общие данные
		element->SetAttribute("ID", entity->GetName().c_str());
		element->SetAttribute("Type", entity->GetType().c_str());

		// Сохраняем координты, угол, масштаб
		char position[256];
		sprintf(position, "%d, %d", entity->GetPosition().x, entity->GetPosition().y);
		element->SetAttribute("Position", position);
		element->SetAttribute("Angle", entity->GetAngle());
		element->SetAttribute("Scale", entity->GetScale());

		return element;
	}

	TiXmlElement* DynamicLevelSerialiser::SerialiseWorld()
	{
		TiXmlElement* elemet = new TiXmlElement("Data");

		FactoryPtr factory = FactoryManager::GetSingleton();

		CategoryPtr levels = FactoryManager::GetSingleton()->GetMasterFile()->GetCategory("Levels");
		for (int i = 0; i < levels->GetSize(); ++i)
		{
			LevelPtr level = levels->GetEntry<LevelEntry>(i)->data;
			elemet->InsertEndChild(*Serialise(level));
		}

		return elemet;
	}

	TiXmlElement* DynamicLevelSerialiser::SerialiseLayer( LayerPtr layer )
	{
		TiXmlElement* layerElement = new TiXmlElement("Layer");

		for (int i = 0; i < layer->Size(); ++i)
		{
			layerElement->InsertEndChild(*SerialiseEntity(layer->GetEntity(i)));
		}

		return layerElement;
	}

};