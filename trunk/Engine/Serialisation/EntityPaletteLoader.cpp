#include "IsilmePCH.h"
#include "EntityPaletteLoader.h"
#include "Core/FactoryManager.h"
#include "Palette/BehaviourPalette.h"
#include "Palette/GraphicsPalette.h"
#include "Palette/EntityPalette.h"
#include "Core/MasterFile.h"

namespace serialisation
{

	EntityPaletteLoader::EntityPaletteLoader()
	{

	}

	EntityPaletteLoader::~EntityPaletteLoader()
	{

	}

	EntryPtr EntityPaletteLoader::LoadEntry( std::string filename )
	{
		ContainerEntry<EntityPalette>* entry = new ContainerEntry<EntityPalette>(filename);

		TiXmlDocument document(filename.c_str());
		document.LoadFile();

		entry->data = Load(document.RootElement());
		return EntryPtr(entry);
	}

	EntityPalettePtr EntityPaletteLoader::Load( TiXmlElement* element )
	{
		EntityPalettePtr palette = FactoryManager::GetSingleton()->GetEntityPalette();

		TiXmlElement* defElement = element->FirstChildElement("Entity");

		EntityDefPtr def;
		while (defElement)
		{
			std::string type = defElement->Attribute("Type");

			char* attr;
			/// Читаем графику
			attr = (char*)(defElement->Attribute("Graphics"));
			GraphicsDefPtr graphics = FactoryManager::GetSingleton()->GetGraphicsPalette()->GetDefinition(attr);

			/// Читаем поведение
			TiXmlElement* bElement = defElement->FirstChildElement("Behaviour");
			attr = (char*)(defElement->Attribute("Behaviour"));
			if (!attr)
				attr = "Default";
			BehaviourFactoryPtr bf = FactoryManager::GetSingleton()->GetBehaviourPalette()->GetFactory(attr);
			if (!bf)
				bf = FactoryManager::GetSingleton()->GetBehaviourPalette()->GetDefaultFactory();
			BehaviourDefPtr behaviour = bf->LoadDefinition(bElement);

			/// Читаем физику
			BodyDef* body = new BodyDef();
			TiXmlElement* bodyElement = defElement->FirstChildElement("Body");
			body->Parse(bodyElement);

			/// Создаем определение
			def = EntityDefPtr(new EntityDefinition(body, graphics, behaviour));
			def->mType = type;

			palette->AddDefinition(def);

			defElement = defElement->NextSiblingElement("Entity");
		}
		return palette;
	}

}