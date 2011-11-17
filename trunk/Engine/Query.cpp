#include "Isilme.h"
#include "Query.h"
#include "Entity.h"

Query::Query()
{

}

Query::~Query()
{

}

int Query::GetEntitiesCount()
{
	return mEntities.size();
}

EntityPtr Query::GetEntity(int index)
{
	if (index < mEntities.size())
		return mEntities.at(index);
	return EntityPtr();
}

void Query::PushEntity(EntityPtr entity)
{
	mEntities.push_back(entity);
}

void Query::Clear()
{

	mEntities.clear();
}