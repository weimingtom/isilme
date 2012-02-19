#ifndef ISILME_SERIALISATION_GRAPHICSPALETTELOADER_H
#define ISILME_SERIALISATION_GRAPHICSPALETTELOADER_H

#include "Definitions.h"
#include "Types.h"
#include "EntryLoader.h"

namespace serialisation
{
	class GraphicsPaletteLoader : public EntryLoader
	{
	public:
		GraphicsPaletteLoader();
		virtual ~GraphicsPaletteLoader();

		virtual EntryPtr LoadEntry(std::string filename);
	};
}
#endif