#include "Isilme.h"
#include "Joints.h"

Level::Level()
{
		
	mPhisicsTimer = 1.0f / 30.0f;
	mCamera = new Camera();
	mWorld = Box2DEngine::GetSingleton()->CreateWorld();
}

Level::~Level()
{
}

LayerList*	Level::GetLayers()
{
	return &mLayers;
}

EntityPtr	Level::CreateEntity(std::string type, float x, float y, float angle, std::string name)
{
	EntityPtr entity = FactoryManager::GetSingleton()->CreateEntity(type, name, shared_from_this());
	entity->SetPosition(x, y);
	entity->SetAngle(angle);
	mLayers.back()->Add(entity);
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
		FactoryManager::GetSingleton()->DestroyEntity(*it);
		mEntities.erase(*it);
	}

	
	mPhisicsTimer = elapsedTime;

	mWorld->Step(elapsedTime, 6, 2);
	mWorld->ClearForces();
	

	mCamera->Update(elapsedTime);
}

void		Level::Load(std::string fileName)
{
	Clear();

	LevelLoader::GetSingleton()->LoadLevel(shared_from_this(), fileName);
}

LayerPtr	Level::AddLayer(std::string name)
{
	if (mLayerNames.find(name) == mLayerNames.end())
	{
		LayerPtr layer(new Layer());
		mLayers.push_back(layer);
		mLayerNames[name] = layer;

		return layer;
	}
	else
	{
		return  mLayerNames[name];
	}
}
