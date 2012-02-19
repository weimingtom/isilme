#ifndef ISILME_CORE_SERIALISATION_LEVELLOADER_H
#define ISILME_CORE_SERIALISATION_LEVELLOADER_H

#include "Definitions.h"
#include "Types.h"
#include "EntryLoader.h"

namespace serialisation
{
	/// @class LevelLoader
	/// Loader for levels
	class LevelLoader : public EntryLoader
	{
	public:
		LevelLoader();
		virtual ~LevelLoader();

		virtual EntryPtr LoadEntry(std::string filename);
		LevelPtr LoadLevel( std::string filename );
	};
}

#endif