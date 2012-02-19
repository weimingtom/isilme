#include "IsilmePCH.h"
#include "ItemsPalette.h"
#include "Definitions.h"
#include "Inventory/ItemDef.h"


ItemsPalette::ItemsPalette()
{

}

ItemsPalette::~ItemsPalette()
{

}

void ItemsPalette::Clear()
{
	mDefinitions.clear();
}

inventory::ItemPtr ItemsPalette::CreateItem( std::string tag )
{
	DefMap::iterator it = mDefinitions.find(tag);
	if (it != mDefinitions.end())
		return it->second->Create();

	return inventory::ItemPtr();
}

inventory::ItemFactoryPtr ItemsPalette::GetFactory( std::string type )
{
	FactoriesMap::iterator it = mFactories.find(type);
	if (it != mFactories.end())
		return it->second;

	return inventory::ItemFactoryPtr();
}

void ItemsPalette::AddDefinition( inventory::ItemDefPtr def )
{
	mDefinitions[def->Tag] = def;
}

void ItemsPalette::RegisterFactory( std::string type, inventory::ItemFactoryPtr factory )
{
	mFactories[type] = factory;
}
