#include "IsilmePCH.h"
#include "Entity.h"
#include "Level.h"
#include "Bodies.h"
#include "FactoryManager.h"

Layer::Layer()
{
	isVisible = true;
};

std::string Layer::GetName()
{
	return mName;
}

void		Layer::Add(EntityPtr object)
{
	// Если объект был на каком-либо другом слое, удаляем его с этого слоя
	if (object->GetLayer() != 0)
	{
		std::vector<EntityPtr>* lst = &(object->GetLayer()->mObjects);
		std::vector<EntityPtr>::iterator it = std::find(lst->begin(), lst->end(), object);
		lst->erase(it);
	}

	// Помещаем в список объектов слоя
	mObjects.push_back(object);
	
	// Привязываем тело к уровню
	object->GetBody()->AttachToLevel(GetLevel());
	
	// Привязываем сущность к уровню
	object->mLevel = GetLevel();
	object->mLayer = shared_from_this();

	// Добавляем объект на уровень
	GetLevel()->mEntities.insert(object);
}

void		Layer::Remove(EntityPtr object)
{
	std::vector<EntityPtr>::iterator it = std::find(mObjects.begin(), mObjects.end(), object);

	if (it != mObjects.end())
	{
		mObjects.erase(it);

		// Снимаем привязку тела к слою
		object->GetBody()->AttachToLevel(LevelPtr());

		object->mLayer.reset();
		object->mLevel.reset();
	}
	else
	{
		LOG_W("Trying to remove entity from layer which doesn't contain it");
	}
}

void		Layer::Clear()
{
	FactoryPtr factory = FactoryManager::GetSingleton();

	///  Уничтожаем объекты слоя
	for (std::vector<EntityPtr>::iterator it = mObjects.begin(); it != mObjects.end(); ++it)
	{
		factory->DestroyEntity(*it);
	}

	/// Очищаем список
	mObjects.clear();
}

EntityPtr	Layer::GetEntity(int index)
{
	return mObjects.at(index);
}

int			Layer::Size()
{
	return mObjects.size();
}

Layer::~Layer()
{
}

LevelPtr	Layer::GetLevel()
{
	return mLevel.lock();
}

void Layer::SetName( std::string name )
{
	LevelPtr level = mLevel.lock();
	if (level)
	{
		level->RenameLayer(mName, name);
	}
	else
	{
		mName = name;
	}
}

bool Layer::IsVisible()
{
	return isVisible;
}

void Layer::SetVisible( bool value )
{
	isVisible = value;
}
