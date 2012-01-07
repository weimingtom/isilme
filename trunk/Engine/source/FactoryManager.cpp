#include "IsilmePCH.h"
#include "FactoryManager.h"
#include "GraphicsFactory.h"
#include "AIPackageFactory.h"
#include "AIPackage.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Inventory/ItemDef.h"
#include "Engine/Inventory/ItemFactory.h"
#include "Fraction.h"
#include "Rank.h"
#include "Engine/Quest/Conversation.h"
#include "Engine/include/Trigger.h"
#include "Behaviour.h"
#include "Graphics/Animation.h"
#include "Graphics/Sprite.h"
#include "Graphics/Particles.h"
#include "Graphics/TriggerGraphics.h"
#include "Graphics/StateGraphics.h"
#include "Core/Serialisation/SaveData.h"
#include "Core/Serialisation/DynamicLevelSerialiser.h"
#include "Core/Palette/EntityPalette.h"
#include "Core/Serialisation/ConversationLoader.h"
#include "Game.h"
#include "Quest/Story.h"

FactoryPtr FactoryManager::mInstance;

FactoryManager::FactoryManager() : 
	mEntityDefinitions(new EntityPalette())
{
	RegisterBehaviour("Default", new BehaviourFactory<BehaviourDefinition>());
	RegisterBehaviour("Trigger", new BehaviourFactory<TriggerDefinition>());

	RegisterGraphics("Sprite", GraphicsFactory<graphics::SpriteDefinition>::New());
	RegisterGraphics("Animation", GraphicsFactory<graphics::AnimationDefinition>::New());
	RegisterGraphics("Particles", GraphicsFactory<graphics::ParticlesDefinition>::New());
	RegisterGraphics("Trigger", GraphicsFactory<graphics::TriggerDef>::New());

	RegisterCamera("Default", new CameraFactory<CameraDefinition>());
}

FactoryManager::~FactoryManager()
{
}

FactoryPtr FactoryManager::GetSingleton()
{
	if (mInstance == 0)
		mInstance = FactoryPtr(new FactoryManager());
	return mInstance;
}

AIPackagePtr	FactoryManager::GetAIPackage(std::string id)
{
	return mAIPackages[id];
}

void	FactoryManager::LoadAIPackages(TiXmlElement* element)
{
	TiXmlElement* packageElement = element->FirstChildElement();
	while (packageElement)
	{
		std::string packageType = packageElement->Value();

		AIPackageFactoryPtr factory = mAIFactories[packageType];
		if (factory)
		{
			const char* idAttr = packageElement->Attribute("ID");
			if (idAttr)
			{
				std::string id = idAttr;
				AIPackagePtr package = factory->CreatePackage();
				package->Parse(packageElement);
				mAIPackages[id] = package;
			}
			else
			{
				LOG_D("ID was not specified for AI package");
			}
		}
		else
		{
			LOG_D("AI Package type %s not found", packageType.c_str());
		}

		packageElement = packageElement->NextSiblingElement();
	}
}

void	FactoryManager::RegisterAIPackage(std::string type, AIPackageFactoryPtr factory)
{
	mAIFactories[type] = factory;
}

inventory::ItemPtr	FactoryManager::CreateItem(std::string tag)
{
	if (mItemsPalette.find(tag) != mItemsPalette.end())
	{
		return mItemsPalette[tag]->Create();
	}
	else
		return inventory::ItemPtr();
}

void	FactoryManager::RegisterItem(std::string type, inventory::ItemFactoryPtr factory)
{
	mItemFactories[type] = factory;
}

void	FactoryManager::ClearItems()
{
	mItemsPalette.clear();
}

void	FactoryManager::LoadItems(std::string fileName)
{
	TiXmlDocument* document = new TiXmlDocument();
	document->LoadFile(fileName.data());

	TiXmlElement* root = document->RootElement();
	TiXmlElement* defElement = root->FirstChildElement();

	// Загружаем поочередно все элементы с описаниями графики
	while(defElement)
	{
		inventory::ItemDefPtr def = LoadItem(defElement);

		defElement = defElement->NextSiblingElement();
	}
	delete  document;
}

inventory::ItemDefPtr FactoryManager::LoadItem(TiXmlElement* element)
{
	inventory::ItemDefPtr def;
	std::string name = element->Attribute("Tag");
	std::string type = element->Value();

	inventory::ItemFactoryMap::iterator it = mItemFactories.find(type);
	if (it != mItemFactories.end())
	{
		def = it->second->LoadDefinition(element);
		mItemsPalette[name] = def;
	}
	else
	{
		// Какой-то хлам, вывести сообщение о незарегистрированном типе
	}

	return def;
}

Body*	FactoryManager::CreateBody(BodyDef* def)
{
	if (def->Type == BodyDef::SimpleBody)
	{
		SimpleBody* body = new SimpleBody();
		return body;
	}
	else if (def->Type == BodyDef::Box2DBody)
	{
		Box2DBody* body = new Box2DBody(def);
		return body;
	}
	return 0;
}

void			FactoryManager::RegisterBehaviour(std::string type, IBehaviourFactory* factory)
{
	mBehaviourFactories[type] = factory;
}

void			FactoryManager::DestroyEntity(std::string name)
{
	EntityPtr entity = mCreatedEntities[name];
	entity->Remove();
	mCreatedEntities.erase(name);
}

GraphicsPtr		FactoryManager::CreateGraphics(std::string tag)
{
	return mGraphicsDefinitions[tag]->Create();
}

void			FactoryManager::DestroyEntity(EntityPtr entity)
{
	entity->Remove();
	mCreatedEntities.erase(entity->GetName());
}

void			FactoryManager::RegisterGraphics(std::string type, GraphicsFactoryPtr factory)
{
	mGraphicsFactories[type] = factory;
}

EntityPtr		FactoryManager::CreateEntity(std::string type, std::string name)
{
	EntityDefPtr def = mEntityDefinitions->Get(type);
	return CreateEntity(def, name);
}

EntityPtr		FactoryManager::CreateEntity(EntityDefPtr definition, std::string name)
{
	Body* body				= CreateBody(definition->GetBodyDefinition());
	GraphicsPtr graphics	= definition->GetGraphicsDefinition()->Create();
	BehaviourPtr behaviour	= definition->GetBehaviourDefinition()->Create();

	EntityPtr entity(new Entity());
	entity->mGraphics = graphics;
	entity->mBehaviour = behaviour;
	entity->mBody = body;

	graphics->mEntity = entity;
	behaviour->mActor = entity;
	body->SetEntity(entity.get());

	if (name == "")
	{
		std::string prefix = "GameObject_";
		char s[20];
		int n = 0;
		while (mCreatedEntities.find(prefix + _itoa(n, s, 16)) != mCreatedEntities.end())
			++n;
		name = prefix + _itoa(n, s, 16);
	}

	entity->mName = name;
	entity->mType = definition->GetType();

	mCreatedEntities[name] = entity;

	return entity;
}

EntityPtr		FactoryManager::GetEntity(std::string name)
{
	return mCreatedEntities[name];
}

ICameraFactory*	FactoryManager::GetCameraFactory(std::string type)
{
	return mCameraFactories[type];
}

void		FactoryManager::RegisterCamera(std::string type, ICameraFactory* factory)
{
	mCameraFactories[type] = factory;
}

void			FactoryManager::LoadGraphics(std::string fileName)
{
	TiXmlDocument* document = new TiXmlDocument();
	document->LoadFile(fileName.data());

	TiXmlElement* root = document->RootElement();
	TiXmlElement* defElement = root->FirstChildElement();

	// Загружаем поочередно все элементы с описаниями графики
	while(defElement)
	{
		GraphicsDefPtr def = LoadGraphics(defElement);

		defElement = defElement->NextSiblingElement();
	}
	delete  document;
}

GraphicsDefPtr FactoryManager::LoadGraphics(TiXmlElement* element)
{
	
	GraphicsDefPtr def;
	std::string name = element->Attribute("Name");
	std::string type = element->Value();

	GraphicsFactoryMap::iterator it = mGraphicsFactories.find(type);
	if (it != mGraphicsFactories.end())
	{
		def = it->second->LoadDefinition(element);
		mGraphicsDefinitions[name] = def;
	}
	else
	{
		RegisterGraphics(type, GraphicsFactory<graphics::StateGraphicsDef<Behaviour> >::New());
		it = mGraphicsFactories.find(type);
		def = it->second->LoadDefinition(element);
		mGraphicsDefinitions[name] = def;
		// Какой-то хлам, вывести сообщение о незарегистрированном типе
		LOG_W("Graphics type %s is not registred", type.c_str());
	}

	return def;
}

void			FactoryManager::LoadEntities(std::string fileName)
{
	TiXmlDocument* document = new TiXmlDocument();
	document->LoadFile(fileName.data());

	TiXmlElement* root = document->RootElement();
	TiXmlElement* defElement = root->FirstChildElement("Entity");

	EntityDefPtr def;
	while (defElement)
	{
		std::string type = defElement->Attribute("Type");

		char* attr;
		/// Читаем графику
		attr = (char*)(defElement->Attribute("Graphics"));
		GraphicsDefPtr graphics = mGraphicsDefinitions[attr];

		/// Читаем поведение
		TiXmlElement* bElement = defElement->FirstChildElement("Behaviour");
		attr = (char*)(defElement->Attribute("Behaviour"));
		if (!attr)
			attr = "Default";
		IBehaviourFactory* bf = mBehaviourFactories[attr];
		if (bf == 0)
			bf = mBehaviourFactories["Default"];
		BehaviourDefPtr behaviour = bf->LoadDefinition(bElement);

		/// Читаем физику
		BodyDef* body = new BodyDef();
		TiXmlElement* bodyElement = defElement->FirstChildElement("Body");
		body->Parse(bodyElement);

		/// Создаем определение
		def = EntityDefPtr(new EntityDefinition(body, graphics, behaviour));
		def->mType = type;

		mEntityDefinitions->Add(def);

		defElement = defElement->NextSiblingElement("Entity");
	}
	delete document;
}

void	FactoryManager::CreateJoint(JointDefPtr def)
{
	//return new Joint(def);
}

FractionPtr		FactoryManager::GetFraction(std::string fractionID)
{
	return mFractions[fractionID];
}

void			FactoryManager::LoadDataFile(std::string fileName)
{
	LOG_M("Loading data file %s", fileName.c_str());

	// Открываем документ
	TiXmlDocument* document = new TiXmlDocument();
	document->LoadFile(fileName.data());

	TiXmlElement* root = document->RootElement();

	// Загружаем фракции
	TiXmlElement* fractionsElement = root->FirstChildElement("Fractions");
	if (fractionsElement)
		LoadFractions(fractionsElement);

	// Загружаем пакеты ИИ
	TiXmlElement* aiPackagesElement = root->FirstChildElement("AIPackages");
	if (aiPackagesElement)
		LoadAIPackages(aiPackagesElement);

	// Загружаем квесты
	// Загружаем предметы
	// Загружаем графику
	// Загружаем поведение

	// закрываем документ
	delete document;
}

void			FactoryManager::LoadFractions(TiXmlElement* element)
{
	std::map<std::pair<std::string, std::string>, int> relations;
	// Загружаем фракции
	TiXmlElement* fractionElement = element->FirstChildElement("Fraction");

	while (fractionElement)
	{
		// Читаем аттрибуты
		const char* idAttr = fractionElement->Attribute("ID");
		const char* nameAttr = fractionElement->Attribute("Name");

		if (idAttr)
		{
			FractionPtr fraction(new Fraction());

			// Идентификатор фракции
			fraction->mID = idAttr;

			// Название фракции
			fraction->mName = nameAttr ? nameAttr : "";

			// Агрессивность
			fraction->mAgression = 0;
			fractionElement->QueryIntAttribute("Agression", &(fraction->mAgression));

			// Ранги
			TiXmlElement* rankElement = fractionElement->FirstChildElement("Rank");
			while (rankElement)
			{
				int rankID = 0;
				rankElement->QueryIntAttribute("ID", &rankID);

				if (rankID)
				{
					RankPtr rank(new Rank());
					rank->mID = rankID;

					fraction->mRanks[rankID] = rank;
				}
				else
				{
					LOG_W("Rank of %s fraction has no ID", idAttr);
				}
				rankElement = rankElement->NextSiblingElement("Rank");
			}

			// Отношения
			TiXmlElement* attitudeElement = fractionElement->FirstChildElement("Attitude");
			while (attitudeElement)
			{
				const char* otherFraction = attitudeElement->Attribute("Fraction");
				int attitude = 0;
				attitudeElement->QueryIntAttribute("Value", &attitude);

				if (otherFraction)
				{
					relations[std::pair<std::string, std::string>(fraction->GetID(), otherFraction)] = attitude;
				}

				attitudeElement = attitudeElement->NextSiblingElement("Attitude");
			}

			// Запоминаем фракцию
			mFractions[fraction->mID] = fraction;
		}
		else
		{
			LOG_W("Fraction has no ID");
		}

		fractionElement = fractionElement->NextSiblingElement("Fraction");
	}

	// Загружаем отношения между фракциями
	for (std::map<std::pair<std::string, std::string>, int>::iterator it = relations.begin(); it != relations.end(); ++it)
	{
		FractionPtr f1 = GetFraction(it->first.first);
		FractionPtr f2 = GetFraction(it->first.second);

		if (!f2)
		{
			LOG_W("Cannot set attitude to %s. Fraction doesn\'t exist", it->first.second.c_str());
		}
		else
		{
			f1->SetAttitudeTo(f2, it->second);
		}
	}
}

void	FactoryManager::LoadConversations(std::string fileName)
{
	TiXmlDocument* document = new TiXmlDocument();
	document->LoadFile(fileName.data());

	TiXmlElement* root = document->RootElement();

//	LoadConversations(root);

	delete document;
}

story::ConversationPtr	FactoryManager::GetConversation(std::string id)
{
	return mConversations[id];
}

LevelPtr FactoryManager::GetLevel(std::string id)
{
	std::map<std::string, LevelPtr>::iterator it = mLevels.find(id);
	if (it != mLevels.end())
	{
		return it->second;
	}
	else
	{
		LOG_W("Level %s not found", id.c_str());

		return LevelPtr();
	}
}

LevelPtr FactoryManager::LoadLevel(std::string fileName)
{
	LevelPtr level = Level::Load(fileName);
	mLevels[level->GetName()] = level;
	return level;
}

void FactoryManager::SaveGame( serialisation::SaveDataPtr save )
{
	serialisation::DynamicLevelSerialiser* serialiser = new serialisation::DynamicLevelSerialiser();

	TiXmlElement* saveElement = new TiXmlElement("Save");
	for (std::map<std::string, LevelPtr>::iterator it = mLevels.begin(); it != mLevels.end(); ++it)
	{
		saveElement->InsertEndChild(*(serialiser->Serialise(it->second)));
	}

	TiXmlDocument* document = new TiXmlDocument(save->GetFullPath().c_str());
	document->InsertEndChild(*saveElement);
	document->SaveFile();
	delete document;
	delete serialiser;
}

void FactoryManager::LoadGame( serialisation::SaveDataPtr save )
{

}

EntityPalettePtr FactoryManager::GetEntityPalette()
{
	return mEntityDefinitions;
}

void FactoryManager::LoadMasterFile( std::string fileName )
{
	LOG_M("LoadMasterFile: %s", fileName.c_str());

	TiXmlDocument document(fileName.c_str());
	document.LoadFile();

	if (document.Error())
	{
		LOG_W("File not found");
	}

	TiXmlElement* rootElement = document.FirstChildElement();

	// Загружаем скрипты
	TiXmlElement* scriptsElement = rootElement->FirstChildElement("Scripts");
	if (scriptsElement)
	{
		std::string dirName = Engine::GetSingleton()->GetResourceDirectory() + "/Scripts/";
		TiXmlElement* fileElement = scriptsElement->FirstChildElement("File");
		while (fileElement)
		{
			if (fileElement->GetText())
			{
				std::string fileName = dirName + fileElement->GetText();
				lua_State* state = Engine::GetSingleton()->GetLua()->GetState();
				luaL_dofile(state, fileName.c_str());
			}
			else
			{
				LOG_W("File element contains no file");
			}

			fileElement = fileElement->NextSiblingElement("File");
		}
	}

	// Загружаем графическую палиру
	TiXmlElement* graphicsElement = rootElement->FirstChildElement("Graphics");
	if (graphicsElement)
	{
		std::string dirName = Engine::GetSingleton()->GetResourceDirectory() + "/";
		TiXmlElement* fileElement = graphicsElement->FirstChildElement("File");
		while (fileElement)
		{
			if (fileElement->GetText())
			{
				std::string fileName = dirName + fileElement->GetText();
				LoadGraphics(fileName.c_str());
			}
			else
			{
				LOG_W("File element contains no file");
			}

			fileElement = fileElement->NextSiblingElement("File");
		}
	}

	// Загружаем палитру объектов
	TiXmlElement* entitiesElement = rootElement->FirstChildElement("Entities");
	if (entitiesElement)
	{
		std::string dirName = Engine::GetSingleton()->GetResourceDirectory() + "/";
		TiXmlElement* fileElement = entitiesElement->FirstChildElement("File");
		while (fileElement)
		{
			if (fileElement->GetText())
			{
				std::string fileName = dirName + fileElement->GetText();
				LoadEntities(fileName.c_str());
			}
			else
			{
				LOG_W("File element contains no file");
			}

			fileElement = fileElement->NextSiblingElement("File");
		}
	}

	// Загружаем уровни
	TiXmlElement* levelsElement = rootElement->FirstChildElement("Levels");
	if (levelsElement)
	{
		std::string dirName = Engine::GetSingleton()->GetResourceDirectory() + "/Levels/";
		TiXmlElement* fileElement = levelsElement->FirstChildElement("File");
		while (fileElement)
		{
			if (fileElement->GetText())
			{
				std::string fileName = dirName + fileElement->GetText();
				LoadLevel(fileName.c_str());
			}
			else
			{
				LOG_W("File element contains no file");
			}

			fileElement = fileElement->NextSiblingElement("File");
		}
	}

	// Загружаем квесты
	TiXmlElement* questsElement = rootElement->FirstChildElement("Quests");
	if (questsElement)
	{
		std::string dirName = Engine::GetSingleton()->GetResourceDirectory() + "/Quests/";
		TiXmlElement* fileElement = questsElement->FirstChildElement("File");
		while (fileElement)
		{
			if (fileElement->GetText())
			{
				std::string fileName = dirName + fileElement->GetText();
				Game::GetSingleton()->GetStory()->Load(fileName);
			}
			else
			{
				LOG_W("File element contains no file");
			}

			fileElement = fileElement->NextSiblingElement("File");
		}
	}

	// Загружаем диалоги
	TiXmlElement* conversationsElement = rootElement->FirstChildElement("Conversations");
	if (conversationsElement)
	{
		std::string dirName = Engine::GetSingleton()->GetResourceDirectory() + "/Conversations/";
		TiXmlElement* fileElement = conversationsElement->FirstChildElement("File");
		while (fileElement)
		{
			if (fileElement->GetText())
			{
				std::string fileName = dirName + fileElement->GetText();
				serialisation::XMLConversationLoader loader;
				story::ConversationPtr conversation = loader.LoadConversation(conversationsElement);
				mConversations[conversation->GetID()] = conversation;
			}
			else
			{
				LOG_W("File element contains no file");
			}

			fileElement = fileElement->NextSiblingElement("File");
		}
	}

	// Загружаем предметы
	TiXmlElement* itemsElement = rootElement->FirstChildElement("Items");
	if (itemsElement)
	{
		std::string dirName = Engine::GetSingleton()->GetResourceDirectory() + "/";
		TiXmlElement* fileElement = itemsElement->FirstChildElement("File");
		while (fileElement)
		{
			if (fileElement->GetText())
			{
				std::string fileName = dirName + fileElement->GetText();
				LoadItems(fileName);
			}
			else
			{
				LOG_W("File element contains no file");
			}

			fileElement = fileElement->NextSiblingElement("File");
		}
	}

	LOG_M("Success");
}
