#include "IsilmePCH.h"
#include "BehaviourPalette.h"

BehaviourPalette::BehaviourPalette()
{

}

BehaviourPalette::~BehaviourPalette()
{

}

BehaviourFactoryPtr BehaviourPalette::GetDefaultFactory()
{
	return GetFactory("Default");
}

void BehaviourPalette::RegisterBehaviour( std::string type, BehaviourFactoryPtr factory )
{
	mBehaviourFactories[type] = factory;
}

BehaviourFactoryPtr BehaviourPalette::GetFactory( std::string type )
{
	BehaviourFactoryMap::iterator it  = mBehaviourFactories.find(type);
	if (it != mBehaviourFactories.end())
		return it->second;

	return BehaviourFactoryPtr();
}
