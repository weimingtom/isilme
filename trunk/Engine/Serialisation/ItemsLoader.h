#ifndef ISILME_SERIALISATION_ITEMSLOADER_H
#define ISILME_SERIALISATION_ITEMSLOADER_H

#include "Definitions.h"
#include "EntryLoader.h"

namespace serialisation
{
	class ISILME_API ItemsLoader : public EntryLoader
	{
	public:
		ItemsLoader();
		virtual ~ItemsLoader();

		virtual EntryPtr LoadEntry(std::string filename) override;
	protected:
		inventory::ItemDefPtr LoadItem(TiXmlElement* element);
	};

}

#endif