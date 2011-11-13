#include "Isilme.h"
#include "GraphicsFactory.h"
#include "AIPackageFactory.h"
#include "AIPackage.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Inventory/ItemDef.h"
#include "Engine/Inventory/ItemFactory.h"
#include "Fraction.h"
#include "Rank.h"
#include "Engine/Quest/Conversation.h"


FactoryPtr FactoryManager::mInstance;

FactoryManager::FactoryManager()
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

EntityPtr		FactoryManager::CreateEntity(std::string type, std::string name, LevelPtr level)
{
	EntityDefPtr def = mEntityDefinitions[type];
	return CreateEntity(def, name, level);
}

EntityPtr		FactoryManager::CreateEntity(EntityDefPtr definition, std::string name, LevelPtr level)
{
	definition->GetBodyDefinition()->World = level->GetWorld();

	Body* body				= CreateBody(definition->GetBodyDefinition());
	GraphicsPtr graphics	= definition->GetGraphicsDefinition()->Create();
	BehaviourPtr behaviour	= definition->GetBehaviourDefinition()->Create();

	EntityPtr entity = EntityPtr(Entity::New(level, behaviour, body, graphics));
	level->mEntities.insert(entity);
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
		BehaviourDefPtr behaviour = mBehaviourFactories[attr]->LoadDefinition(bElement);

		/// Читаем физику
		BodyDef* body = new BodyDef();
		TiXmlElement* bodyElement = defElement->FirstChildElement("Body");
		body->Parse(bodyElement);

		/// Создаем определение
		def = EntityDefPtr(new EntityDefinition(body, graphics, behaviour));

		mEntityDefinitions[type] = def;

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

void	FactoryManager::LoadConversations(TiXmlElement* element)
{
	TiXmlElement* convElement = element->FirstChildElement("Conversation");
	while (convElement)
	{
		story::ConversationPtr conversation = story::Conversation::Load(convElement);
		if (conversation)
		{
			mConversations[conversation->GetID()] = conversation;
		}

		convElement = convElement->NextSiblingElement("Conversation");
	}
}

void	FactoryManager::LoadConversations(std::string fileName)
{
	TiXmlDocument* document = new TiXmlDocument();
	document->LoadFile(fileName.data());

	TiXmlElement* root = document->RootElement();

	LoadConversations(root);

	delete document;
}

story::ConversationPtr	FactoryManager::GetConversation(std::string id)
{
	return mConversations[id];
}