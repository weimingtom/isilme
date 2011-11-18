#include "IsilmePCH.h"
#include "StaticLevelSerialiser.h"
#include "FactoryManager.h"
#include "Level.h"
#include "Layer.h"
#include "Entity.h"

namespace serialisation
{
	XMLStaticLevelSerialiser::XMLStaticLevelSerialiser()
	{

	}

	XMLStaticLevelSerialiser::~XMLStaticLevelSerialiser()
	{
	
	}

	TiXmlElement* XMLStaticLevelSerialiser::SerialiseEntity(EntityPtr entity)
	{
		TiXmlElement* entityElement = new TiXmlElement("Entity");

		entityElement->SetAttribute("Name", entity->GetName().c_str());
		entityElement->SetAttribute("Type", entity->GetType().c_str());

		char dummy[256];
		sprintf(dummy, "%f, %f, %f", entity->GetPosition().x, entity->GetPosition().y, entity->GetAngle());
		entityElement->SetAttribute("Position", dummy);
		entityElement->SetAttribute("Scale", entity->GetScale());
		return entityElement;
	}

	TiXmlElement* XMLStaticLevelSerialiser::SerialiseLayer(LayerPtr layer)
	{
		TiXmlElement* layerElement = new TiXmlElement("Layer");

		for (int i = 0; i < layer->Size(); ++i)
		{
			EntityPtr e = layer->GetEntity(i);
			layerElement->InsertEndChild(*SerialiseEntity(e));
		}

		return layerElement;
	}

	TiXmlElement* XMLStaticLevelSerialiser::Serialise(LevelPtr level)
	{
		TiXmlElement* levelElement = new TiXmlElement("Level");

		// Записываем имя уровня
		levelElement->SetAttribute("Name", level->GetName().c_str());

		// Записываем камеру
		// Записываем физику
		// Записываем слои
		for (int i = 0; i < level->GetLayersCount(); ++i)
		{
			LayerPtr layer = level->GetLayer(i);
			TiXmlElement* layerElement = SerialiseLayer(layer);
			levelElement->InsertEndChild(*layerElement);
		}

		return levelElement;
	}

	void XMLStaticLevelSerialiser::Serialise(LevelPtr level, std::string fileName)
	{
		TiXmlElement* root = Serialise(level);
		TiXmlDocument* document = new TiXmlDocument(fileName.c_str());
		document->InsertEndChild(*root);
		document->SaveFile();
		delete document;
	}
};