#ifndef ISILME_SERIALISATION_STORYLOADER_H
#define ISILME_SERIALISATION_STORYLOADER_H

#include "Definitions.h"
#include "Types.h"
#include "EntryLoader.h"

#include "Story/Story.h"
#include "Story/Quest.h"
#include "Story/Stage.h"

namespace serialisation
{
	/// @class StoryLoader
	class ISILME_API StoryLoader : public EntryLoader
	{
	public:
		StoryLoader();
		virtual ~StoryLoader();

		virtual EntryPtr LoadEntry(std::string filename);
	protected:
		virtual story::StagePtr LoadStage(TiXmlElement* element);
		virtual story::QuestPtr LoadQuest(TiXmlElement* element);
		virtual story::StoryPtr LoadStory(TiXmlElement* element);
		virtual story::StoryPtr LoadStory(std::string fileName);

	};
}
#endif