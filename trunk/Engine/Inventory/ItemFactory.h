#ifndef ISILME_INVENTORY_ITEMFACTORY_H
#define ISILME_INVENTORY_ITEMFACTORY_H

#include "Definitions.h"
#include "Inventory.h"
#include "ItemDef.h"

namespace inventory
{
	class ISILME_API IItemFactory
	{
	public:
		virtual ItemDefPtr	LoadDefinition(TiXmlElement* graphicsElement) = 0;
	private:
	};

	template <class T>
	class ItemFactory : public IItemFactory
	{
	public:
		static ItemFactoryPtr New()
		{
			return ItemFactoryPtr(new ItemFactory<T>());
		}

		ItemFactory()
		{
		}
		virtual ~ItemFactory()
		{
		}
		virtual ItemDefPtr	LoadDefinition(TiXmlElement* def)
		{
			T* itemDef = new T();
			itemDef->Parse(def);
			return ItemDefPtr(itemDef);
		}
	private:
	};
};

#endif