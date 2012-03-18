#ifndef ISILME_SERIOALISATION_SCRIPTLOADER_H
#define ISILME_SERIOALISATION_SCRIPTLOADER_H

#include "Definitions.h"
#include "Types.h"
#include "EntryLoader.h"

namespace serialisation
{
	class ScriptLoader : public EntryLoader
	{
	public:
		ScriptLoader();
		virtual ~ScriptLoader();

		virtual EntryPtr LoadEntry(std::string filename);
	};
}

#endif