#include "Isilme.h"
#include "Joints.h"

namespace RayCast
{
	enum Mode
	{
		Nearest = 0,
		All = 1,
		Any = 2
	};
};

class RayQueryImpl : public b2RayCastCallback
{
public:
	RayQueryImpl(b2World* world, float x1, float y1, float x2, float y2)
	{
		mWorld = world;
		mPoint1.Set(x1, y1);
		mPoint2.Set(x2, y2);
	}

	virtual ~RayQueryImpl()
	{
	}

	bool ExecuteAll(EntityList* entities)
	{
		mEnties = entities;
		mMode = RayCast::All;

		mWorld->RayCast(this, mPoint1, mPoint2);

		return mEnties->size() > 0;
	}

	EntityPtr	ExecuteNearest()
	{
		mEntity.reset();
		mMode = RayCast::Nearest;

		mWorld->RayCast(this, mPoint1, mPoint2);

		return mEntity;
	}

	bool	ExecuteAny()
	{
		mEntity.reset();
		mMode = RayCast::Any;

		mWorld->RayCast(this, mPoint1, mPoint2);

		return mEntity != 0;
	}

	virtual float32 ReportFixture(b2Fixture* fixture, const Vector2& point, const Vector2& normal, float32 fraction)
	{
		if (mMode == RayCast::Nearest)
		{
			if (minFraction > fraction || mEntity == 0)
			{
				minFraction = fraction;
				Entity* e = (Entity*)(fixture->GetBody()->GetUserData());
				BehaviourPtr b = e->GetBehaviour();
				mEntity = b->GetActor();
			}

			return fraction;
		}
		else if (mMode == RayCast::All)
		{
			EntityPtr entity = ((Entity*)(fixture->GetBody()->GetUserData()))->GetBehaviour()->GetActor();
			mEnties->push_back(entity);
			return 1;
		}
		else if (mMode ==RayCast::Any)
		{
			mEntity = ((Entity*)(fixture->GetBody()->GetUserData()))->GetBehaviour()->GetActor();
			return 0;
		}
	}

private:
	b2World* mWorld;
	float32 minFraction;
	EntityList* mEnties;
	EntityPtr mEntity;
	Vector2 mPoint1;
	Vector2 mPoint2;
	RayCast::Mode mMode;
};

class AABBQueryImpl : public b2QueryCallback
{
public:
	AABBQueryImpl(b2World* world, float x1, float y1, float x2, float y2)
	{
		mAABB.lowerBound.Set(x1 < x2 ? x1 : x2, y1 < y2 ? y1 : y2);
		mAABB.upperBound.Set(x1 > x2 ? x1 : x2, y1 > y2 ? y1 : y2);

		mWorld = world;
	}

	virtual ~AABBQueryImpl()
	{
		mEnties = 0;
	}

	bool	Execute(EntityList* entities)
	{
		mEnties = entities;

		mEnties->clear();

		mWorld->QueryAABB(this, mAABB);

		return mEnties->size() > 0;
	}

	bool ReportFixture(b2Fixture* fixture)
	{
		EntityPtr entity = ((Entity*)(fixture->GetBody()->GetUserData()))->GetBehaviour()->GetActor();
		mEnties->push_back(entity);
		return true;
	}
private:
	b2World* mWorld;
	b2AABB mAABB;
	EntityList* mEnties;
};

std::string Level::GetName()
{
	return mName;
}

Level::Level()
{
		
	mPhisicsTimer = 1.0f / 30.0f;
	mCamera = new Camera();
	mWorld = Box2DEngine::GetSingleton()->CreateWorld();
}

Level::~Level()
{
}

LayerPtr	Level::GetLayer(int index)
{
	return mLayers.at(index);
}

int	Level::GetLayersCount()
{
	return mLayers.size();
}

void	Level::AddLayer(LayerPtr layer)
{
	mLayers.push_back(layer);
	mLayerNames[layer->GetName()] = layer;
}

void	Level::RemoveLayer(LayerPtr layer)
{
	std::vector<LayerPtr>::iterator it = std::find(mLayers.begin(), mLayers.end(), layer);
	if (it != mLayers.end())
	{
		mLayers.erase(it);
		mLayerNames.erase(layer->GetName());
	}
	else
	{
		LOG_W("Trying to remove layer from level which doesn't contain it");
	}
}

EntityPtr	Level::CreateEntity(std::string type, float x, float y, float angle, std::string name)
{
	// Создаем сущность
	EntityPtr entity = FactoryManager::GetSingleton()->CreateEntity(type, name);

	// Помещаем сущность на слой
	mLayers.back()->Add(entity);

	// Устанавливаем координаты тела
	entity->SetPosition(x, y);
	entity->SetAngle(angle);

	return entity;
}

void		Level::Clear()
{
	mLayers.clear();
	mLayerNames.clear();
}

LayerPtr		Level::GetLayer(std::string name)
{
	LayerMap::iterator it = mLayerNames.find(name);
	if (it != mLayerNames.end())
		return it->second;
	else
	{
		return AddLayer(name);
	}
}

Camera*		Level::GetCamera()
{
	return mCamera;
}

void		Level::SetCamera(Camera* camera)
{
	mCamera = camera;
}

b2World*	Level::GetWorld()
{
	return mWorld;
}

void		Level::Update(float elapsedTime)
{
	EntitySet destroyed;

	EntitySet::iterator it = mEntities.begin();
	while (it != mEntities.end())
	{
		EntityPtr entity = *it;
		entity->Update(elapsedTime);

		if (entity->IsRemoved())
		{
			entity->GetLayer()->Remove(entity);
			destroyed.insert(entity);
			++it;
		}
		else
		{
			++it;
		}
	}

	for (EntitySet::iterator it = destroyed.begin(); it != destroyed.end(); ++it)
	{
//		FactoryManager::GetSingleton()->DestroyEntity(*it);
		mEntities.erase(*it);
	}

	
	mPhisicsTimer = elapsedTime;

	mWorld->Step(elapsedTime, 6, 2);
	mWorld->ClearForces();
	

	mCamera->Update(elapsedTime);
}

LayerPtr	Level::AddLayer(std::string name)
{
	if (mLayerNames.find(name) == mLayerNames.end())
	{
		LayerPtr layer(new Layer());
		mLayers.push_back(layer);
		layer->mLevel = shared_from_this();
		layer->mName = name;
		mLayerNames[name] = layer;

		return layer;
	}
	else
	{
		return  mLayerNames[name];
	}
}

bool	Level::RayCastQueryAll(EntityList* dest, float x1, float y1, float x2, float y2, int count)
{
	RayQueryImpl query(GetWorld(), x1, y1, x2, y2);
	return query.ExecuteAll(dest);
}

EntityPtr	Level::RayCastQueryNearest(float x1, float y1, float x2, float y2)
{
	RayQueryImpl query(GetWorld(), x1, y1, x2, y2);
	return query.ExecuteNearest();
}

bool	Level::RayCastQueryAny(float x1, float y1, float x2, float y2)
{
	RayQueryImpl query(GetWorld(), x1, y1, x2, y2);
	return query.ExecuteAny();
}

bool		Level::AABBQuery(EntityList* dest, float x1, float y1, float x2, float y2)
{
	AABBQueryImpl query(GetWorld(), x1, y1, x2, y2);
	return query.Execute(dest);
}

void	ParseWorld(LevelPtr level, TiXmlElement* rootElement)
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

void	ParseCamera(LevelPtr level, TiXmlElement* rootElement)
{
	TiXmlElement* cameraElement = rootElement->FirstChildElement("Camera");

	const char* attr = cameraElement ? cameraElement->Attribute("Type") : 0;
	std::string type = attr ? attr : "Default";

	ICameraFactory* factory = FactoryManager::GetSingleton()->GetCameraFactory(type);

	Camera* camera = factory->LoadDefinition(cameraElement)->Create();
	level->SetCamera(camera);

}

void	ParseEntity(LayerPtr layer, TiXmlElement* entityElement)
{
	// Читаем тип сущности и ее имя
	const char* typeAttr = entityElement->Attribute("Type");
	const char* nameAttr = entityElement->Attribute("Name");

	// Если не указан тип сущности, пропускаем эелемент
	if (!typeAttr)
	{
		LOG_E("Entity XML element doesn't contain entity type");
		return;
	}

	// Создаем сущность
	EntityPtr entity = FactoryManager::GetSingleton()->CreateEntity(typeAttr, nameAttr ? nameAttr : "");

	// Помещаем сущность на слой
	layer->Add(entity);

	//Читаем координаты сущности
	const char* positionAttr = entityElement->Attribute("Position");
	float x = 0.0f;
	float y = 0.0f;
	float angle = 0.0f;

	if (positionAttr)
	{
		sscanf(positionAttr, "%f, %f, %f", &x, &y, &angle);
	}
	
	entity->SetPosition(x, y);
	entity->SetAngle(angle);
}

void ParseLayers(LevelPtr level, TiXmlElement* rootElement)
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
				ParseEntity(layer, element);
			}
			else
			{
				LOG_W("Layer XML element contains ivalid child element");
			}

			element = element->NextSiblingElement();
		}
		layerElement = layerElement->NextSiblingElement("Layer");
	}
}

void ParseScripts(LevelPtr level, TiXmlElement* rootElement)
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

	if (scriptsElement->Attribute("StartScript"))
	{
		const char* sc = scriptsElement->Attribute("StartScript");
		luaL_dostring(lua->GetState(), sc);
	}

}

void ParseJoints(LevelPtr level, TiXmlElement* rootElement)
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

LevelPtr	Level::Load(TiXmlElement* levelElement)
{
	LevelPtr level(new Level());

	ParseWorld(level, levelElement);
	ParseCamera(level, levelElement);
	ParseLayers(level, levelElement);
	ParseScripts(level, levelElement);
	ParseJoints(level, levelElement);

	return level;
}

LevelPtr	Level::Load(std::string fileName)
{
	TiXmlDocument* document = new TiXmlDocument();
	document->LoadFile(fileName.data());

	TiXmlElement* root = document->RootElement();

	LevelPtr level = Level::Load(root);

	delete document;

	return level;
}