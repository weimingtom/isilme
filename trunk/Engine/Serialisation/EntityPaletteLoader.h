#ifndef ISILME_CORE_SERIALISATION_H
#define ISILME_CORE_SERIALISATION_H

#include "Definitions.h"
#include "Types.h"
#include "EntryLoader.h"

namespace serialisation
{
	/// @class EntityPaletteLoader
	/// Loader for entity palette
	class ISILME_API EntityPaletteLoader : public EntryLoader
	{
	public:
		EntityPaletteLoader();
		virtual ~EntityPaletteLoader();

		virtual EntryPtr LoadEntry(std::string filename);
	protected:
		EntityPalettePtr Load(TiXmlElement* element);
	};
}
#endif