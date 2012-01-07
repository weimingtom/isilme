#ifndef ISILME_SERIALISATION_STORYLOADER_H
#define ISILME_SERIALISATION_STORYLOADER_H

#include "Definitions.h"
#include "Quest/Story.h"
#include "Quest/Quest.h"
#include "Quest/Stage.h"

namespace serialisation
{
	class ISILME_API IStoryLoader
	{
	public:
		virtual story::StoryPtr LoadStory(std::string fileName) = 0;

	};

	class ISILME_API XMLStoryLoader
	{
	public:
		XMLStoryLoader();
		virtual ~XMLStoryLoader();

		virtual story::StagePtr LoadStage(TiXmlElement* element);
		virtual story::QuestPtr LoadQuest(TiXmlElement* element);
		virtual story::StoryPtr LoadStory(TiXmlElement* element);
		virtual story::StoryPtr LoadStory(std::string fileName);

	};
}
#endif