#ifndef ISILME_SERIALISATION_STORYSERIALISER_H
#define ISILME_SERIALISATION_STORYSERIALISER_H

#include "Definitions.h"
#include "Quest/Story.h"
#include "Quest/Quest.h"
#include "Quest/Stage.h"

namespace serialisation
{
	class ISILME_API IStorySerialiser
	{
	public:
		virtual void Serialise(story::StoryPtr story, std::string fileNmae) = 0;
	};

	class ISILME_API XMLStorySerialiser : public IStorySerialiser
	{
	public:
		XMLStorySerialiser();
		virtual ~XMLStorySerialiser();

		virtual void SerialiseStage(story::StagePtr stage, TiXmlElement* element);
		virtual void SerialiseQuest(story::QuestPtr quest, TiXmlElement* element);
		virtual void SerialiseStory(story::StoryPtr story, TiXmlElement* element);

		virtual void Serialise(story::StoryPtr story, std::string fileNmae);
	};
}
#endif