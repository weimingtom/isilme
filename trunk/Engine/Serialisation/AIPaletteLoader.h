#ifndef ISILME_SERIOALISATION_AIPALETTELOADER_H
#define ISILME_SERIOALISATION_AIPALETTELOADER_H

#include "Definitions.h"
#include "Types.h"
#include "EntryLoader.h"

namespace serialisation
{
	class AIPaletteLoader : public EntryLoader
	{
	public:
		AIPaletteLoader();
		virtual ~AIPaletteLoader();

		virtual EntryPtr LoadEntry(std::string filename);
	};
}

#endif