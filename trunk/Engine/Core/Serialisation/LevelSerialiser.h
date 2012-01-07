#ifndef ISILME_CORE_SERIALISATION_LEVEL_SERIALISER_H
#define ISILME_CORE_SERIALISATION_LEVEL_SERIALISER_H

#include "Definitions.h"

namespace serialisation
{
	/// Serialiser for static level data.
	class ISILME_API LevelSerialiser
	{
	public:
		/// Serialises and writes to file
		///
		/// @param	level   	The level.
		/// @param	fileName	Filename of the file.
		virtual void Serialise(LevelPtr level, std::string fileName) = 0;
	};
};

#endif