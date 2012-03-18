#ifndef ISILME_CORE_SERIALISATION_ENTRYLOADER_H
#define ISILME_CORE_SERIALISATION_ENTRYLOADER_H

#include "../Definitions.h"
#include "Types.h"

namespace serialisation
{
	/// @class EntryLoader
	/// Base class for loading entry in masterfile
	class EntryLoader
	{
	public:
		/// Loads entry from file
		virtual EntryPtr LoadEntry(std::string filename) = 0;
	};
}

#endif