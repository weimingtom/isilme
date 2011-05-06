#include "Isilme.h"

// Parsers

ActionDefinition::ActionDefinition()
{
}

ActionDefinition::~ActionDefinition()
{
}

// LevelLoader

LevelLoader* LevelLoader::mInstance = 0;

LevelLoader::LevelLoader()
{
	FactoryManager::GetSingleton()->LoadGraphics("../Data/Graphics.xml");
	FactoryManager::GetSingleton()->LoadEntities("../Data/Entities.xml");
}

LevelLoader::~LevelLoader()
{
}

LevelLoader*	LevelLoader::GetSingleton()
{
	if (!mInstance)
		mInstance = new LevelLoader();

	return mInstance;
}

void LevelLoader::LoadLevel(LevelPtr level, std::string fileName)
{
	mLevel = level;
	
	TiXmlDocument* document = new TiXmlDocument();
	document->LoadFile(fileName.c_str());

	TiXmlElement* rootElement = document->RootElement();

	ParseWorld(level, rootElement);
	ParseGroups(rootElement);
	ParseLayers(level, rootElement);
	ParseJoints(level, rootElement);
	ParseCamera(level, rootElement);
	ParseScripts(rootElement);

	delete document;
}

void LevelLoader::ParseScripts(TiXmlElement* rootElement)
{
	TiXmlElement* scriptsElement = rootElement->FirstChildElement("Scripts");
	if (scriptsElement == 0)
		return;

	// Читаем и выполняем Lua-сценарии
	Lua* lua = Engine::GetSingleton()->GetLua();
	TiXmlElement* luaElement = scriptsElement->FirstChildElement("Lua");
	while (luaElement)
	{
		lua->DoFile(luaElement->GetText());
		luaElement = luaElement->NextSiblingElement("Lua");
	}
}

void LevelLoader::ParseJoints(LevelPtr level, TiXmlElement* rootElement)
{
	FactoryPtr factory = FactoryManager::GetSingleton();

	TiXmlElement* jointElement = rootElement->FirstChildElement("Joint");

	while( jointElement)
	{
		JointDefPtr def(new JointDefinition());
		def->Parse(jointElement);
		def->world = level->GetWorld();

		factory->CreateJoint(def);

		jointElement = jointElement->NextSiblingElement("Joint");
	}
}

void LevelLoader::ParseLayers(LevelPtr level, TiXmlElement* rootElement)
{
	TiXmlElement* layerElement = rootElement->FirstChildElement("Layer");

	while (layerElement)
	{
		std::string name = layerElement->Attribute("Name");
		LayerPtr layer = level->AddLayer(name);

		TiXmlElement* element = layerElement->FirstChildElement();
		while (element)
		{
			std::string category = element->Value();

			if (category == "Entity")
			{
				EntityData data = ParseEntity(element);
				PlaceEntity(level, layer, data);
			}
			else if (category == "Group")
			{
				GroupData data = ParseGroup(element);
				PlaceGroup(level, layer, data);
			}
			else
			{
			}

			element = element->NextSiblingElement();
		}
		layerElement = layerElement->NextSiblingElement("Layer");
	}
}

void LevelLoader::ParseGroups(TiXmlElement* rootElement)
{
	TiXmlElement* groupElement = rootElement->FirstChildElement("Group");

	while (groupElement)
	{
		std::string name = groupElement->Attribute("Type");

		GroupData group;

		// Читаем список всех сущностей группы
		TiXmlElement* entityElement = groupElement->FirstChildElement("Entity");
		while (entityElement)
		{
			EntityData entity = ParseEntity(entityElement);
			group.entities[entity.name] = entity;

			entityElement = entityElement->NextSiblingElement("Entity");
		}

		// Читаем список всех связей группы
		TiXmlElement* jointElement = groupElement->FirstChildElement("Joint");
		while (jointElement)
		{
			JointDefPtr joint(new JointDefinition());
			joint->Parse(jointElement);
			group.joints.push_back(joint);

			jointElement = jointElement->NextSiblingElement("Joint");
		}

		// Запоминаем группу
		mGroups[name] = group;

		// Переходим к следующему элементу
		groupElement = groupElement->NextSiblingElement("Group");
	}
}

EntityData LevelLoader::ParseEntity(TiXmlElement* entityElement)
{
	EntityData entity;
	entity.angle	= 0.0f;
	entity.x		= 0.0f;
	entity.y		= 0.0f;
	entity.scale	= 1.0f;

	// Считываем позицию сущности
	const char* position = entityElement->Attribute("Position");
	sscanf_s(position, "%f, %f, %f", &entity.x, &entity.y, &entity.angle);
	
	// Считываем имя сущности
	entity.name = entityElement->Attribute("Name");

	// Считываем масштаб сущности
	entityElement->QueryFloatAttribute("Scale", &entity.scale);

	// Считываем тип сущности
	entity.type = entityElement->Attribute("Type");

	//// Считываем скрипты сущности
	//TiXmlElement* scriptsElement = entityElement->FirstChildElement("Scripts");
	//if (scriptsElement)
	//{
	//	TiXmlAttribute* attr = scriptsElement->FirstAttribute();
	//	while (attr)
	//	{
	//		entity.scripts[attr->Name()] = attr->Value();
	//		attr = attr->Next();
	//	}
	//}

	//// Считываем переменные поведения
	//TiXmlElement* behaviourElement = entityElement->FirstChildElement("BehaviourParams");
	//if (behaviourElement)
	//{
	//	TiXmlAttribute* attr = behaviourElement->FirstAttribute();
	//	while (attr)
	//	{
	//		entity.behaviourData[attr->Name()] = attr->Value();
	//		attr = attr->Next();
	//	}
	//}
	return entity;
}

GroupData LevelLoader::ParseGroup(TiXmlElement* groupElement)
{
	std::string type = groupElement->Attribute("Type");
	const char* position = groupElement->Attribute("Position");

	GroupData group = mGroups[type];
	sscanf_s(position, "%f, %f", &group.x, &group.y);

	return group;
}

void	LevelLoader::PlaceEntity(LevelPtr level, LayerPtr layer, EntityData& data)
{
	FactoryPtr factory = FactoryManager::GetSingleton();

	EntityPtr entity = factory->CreateEntity(data.type, data.name, level);

	entity->SetPosition(data.x, data.y);
	entity->SetAngle(data.angle);

	layer->Add(entity);
}

void	LevelLoader::PlaceGroup(LevelPtr level, LayerPtr layer, GroupData& data)
{
	FactoryPtr factory = FactoryManager::GetSingleton();
	EntityMap		placedEntities;

	for (std::map<std::string, EntityData>::iterator it = data.entities.begin(); it != data.entities.end(); ++it)
	{
		EntityPtr entity = factory->CreateEntity(it->second.type, "", level);

		entity->SetPosition(it->second.x + data.x, it->second.y + data.y);
		entity->SetAngle(it->second.angle);

		layer->Add(entity);
		placedEntities[it->second.name] = entity;
	}

	for (std::vector<JointDefPtr>::iterator it = data.joints.begin(); it != data.joints.end(); ++it)
	{
		(*it)->entityA = placedEntities[(*it)->entityA]->GetName();
		(*it)->entityB = placedEntities[(*it)->entityB]->GetName();
		(*it)->world = level->GetWorld();
		
		factory->CreateJoint((*it));
	}
}

void	LevelLoader::ParseCamera(LevelPtr level, TiXmlElement* rootElement)
{
	TiXmlElement* cameraElement = rootElement->FirstChildElement("Camera");

	const char* attr = cameraElement ? cameraElement->Attribute("Type") : 0;
	std::string type = attr ? attr : "Default";

	ICameraFactory* factory = FactoryManager::GetSingleton()->GetCameraFactory(type);

	Camera* camera = factory->LoadDefinition(cameraElement)->Create();
	level->SetCamera(camera);

}

void	LevelLoader::ParseWorld(LevelPtr level, TiXmlElement* rootElement)
{
	TiXmlElement*	worldElement = rootElement->FirstChildElement("World");

	if (!worldElement)
		return;

	Vector2 gravity(0.0f, 9.8f);

	const char* str = worldElement->Attribute("Gravity");
	if (str)
	{
		sscanf_s(str, "%f, %f", &gravity.x, &gravity.y);
	}

	level->GetWorld()->SetGravity(gravity);
}