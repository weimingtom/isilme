#ifndef ISILME_PALETTE_ITEMSPALETTE_H
#define ISILME_PALETTE_ITEMSPALETTE_H

#include "Definitions.h"
#include "Types.h"

class ISILME_API ItemsPalette
{
public:
	ItemsPalette();
	virtual ~ItemsPalette();

	/// Clears the palette
	void Clear();

	/// Creates items by tag
	inventory::ItemPtr CreateItem( std::string tag );

	/// Gets factory of special type
	inventory::ItemFactoryPtr GetFactory( std::string type );

	/// Adds definition to palette
	void AddDefinition( inventory::ItemDefPtr def );

	/// Registers factory for type
	void RegisterFactory( std::string type, inventory::ItemFactoryPtr factory );
private:
	typedef std::map<std::string, inventory::ItemFactoryPtr> FactoriesMap;
	typedef std::map<std::string, inventory::ItemDefPtr> DefMap;

	FactoriesMap mFactories;
	DefMap mDefinitions;
};
#endif