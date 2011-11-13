#include "Isilme.h"

Layer::Layer()
{
		
};

void		Layer::Add(EntityPtr object)
{
	// ���� ������ ��� �� �����-���� ������ ����, ���������� ���
	if (object->GetLayer() != 0)
	{
		object->GetLayer()->mObjects.remove(object);
	}

	mObjects.push_back(object);
	object->OnAddedToLayer(shared_from_this());
}

void		Layer::Remove(EntityPtr object)
{
	mObjects.remove(object);
	object->mLayer = LayerPtr();
}

void		Layer::Clear()
{
	FactoryPtr factory = FactoryManager::GetSingleton();

	///  ���������� ������� ����
	for (EntityList::iterator it = mObjects.begin(); it != mObjects.end(); ++it)
	{
		factory->DestroyEntity(*it);
	}

	/// ������� ������
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

LevelPtr	Layer::GetLevel()
{
	return mLevel.lock();
}