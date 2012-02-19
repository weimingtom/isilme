#ifndef ISILME_SERIALISATION_FRACTIONSLOADER_H
#define ISILME_SERIALISATION_FRACTIONSLOADER_H

#include "Definitions.h"
#include "EntryLoader.h"

namespace serialisation
{
	class ISILME_API FractionsLoader : public EntryLoader
	{
	public:
		FractionsLoader();
		virtual ~FractionsLoader();

		virtual EntryPtr LoadEntry(std::string filename);
	protected:
		void LoadFractions(TiXmlElement* element);
	};
}

#endif