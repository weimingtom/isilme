#include "Isilme.h"

Layer::Layer()
{
		
};

void		Layer::Add(EntityPtr object)
{
	// Если объект был на каком-либо другом слое, перемещаем его
	if (object->GetLayer() != 0)
	{
		object->GetLayer()->mObjects.remove(object);
	}

	mObjects.push_back(object);
	object->OnAddedToLayer(shared_from_this());
}

void		Layer::Clear()
{
	FactoryPtr factory = FactoryManager::GetSingleton();

	///  Уничтожаем объекты слоя
	for (EntityList::iterator it = mObjects.begin(); it != mObjects.end(); ++it)
	{
		factory->DestroyEntity(*it);
	}

	/// Очищаем список
	mObjects.clear();
}

int			Layer::Size()
{
	return mObjects.size();
}

EntityList* Layer::GetObjects()
{
	return &mObjects;
}

Layer::~Layer()
{
}