#include "IsilmePCH.h"
#include "EntityPalette.h"
#include "EntityDefinition.h"

EntityPalette::EntityPalette()
{

}

EntityPalette::~EntityPalette()
{

}

EntityPalette::EntityDefMap* EntityPalette::GetData() 
{
	return &mPalette;
}

EntityDefPtr EntityPalette::Get( std::string type ) 
{
	return mPalette[type];
}

void EntityPalette::Add( EntityDefPtr def )
{
	mPalette[def->GetType()] = def;
}
