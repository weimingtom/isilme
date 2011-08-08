
#include "Isilme.h"
#include "GraphicsFactory.h"


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