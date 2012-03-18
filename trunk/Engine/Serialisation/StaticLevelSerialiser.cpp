#include "IsilmePCH.h"
#include "StaticLevelSerialiser.h"
#include "Core/FactoryManager.h"
#include "Core/Level.h"
#include "Core/Layer.h"
#include "Core/Entity.h"

namespace serialisation
{
	StaticLevelSerialiser::StaticLevelSerialiser()
	{

	}

	StaticLevelSerialiser::~StaticLevelSerialiser()
	{
	
	}

	TiXmlElement* StaticLevelSerialiser::SerialiseEntity(EntityPtr entity)
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

	TiXmlElement* StaticLevelSerialiser::SerialiseLayer(LayerPtr layer)
	{
		TiXmlElement* layerElement = new TiXmlElement("Layer");
		layerElement->SetAttribute("Name", layer->GetName().c_str());

		for (int i = 0; i < layer->Size(); ++i)
		{
			EntityPtr e = layer->GetEntity(i);
			layerElement->InsertEndChild(*SerialiseEntity(e));
		}

		return layerElement;
	}

	TiXmlElement* StaticLevelSerialiser::Serialise(LevelPtr level)
	{
		TiXmlElement* levelElement = new TiXmlElement("Level");
		TiXmlElement* worldElement = new TiXmlElement("World");
		char buf[256];
		sprintf(buf, "%f, %f", level->GetWorld()->GetGravity().x, level->GetWorld()->GetGravity().y);

		worldElement->SetAttribute("Gravity", buf);
		levelElement->InsertEndChild(*worldElement);

		// Записываем имя уровня
		levelElement->SetAttribute("Name", level->GetID().c_str());


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

	void StaticLevelSerialiser::Serialise(LevelPtr level, std::string fileName)
	{
		TiXmlElement* root = Serialise(level);
		TiXmlDocument* document = new TiXmlDocument(fileName.c_str());
		document->InsertEndChild(*root);
		document->SaveFile();
		delete document;
	}
};