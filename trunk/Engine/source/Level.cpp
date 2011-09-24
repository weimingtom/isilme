#include "Isilme.h"
#include "Joints.h"

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