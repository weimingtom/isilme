#include "IsilmePCH.h"
#include "StoryLoader.h"

namespace serialisation
{


	XMLStoryLoader::XMLStoryLoader()
	{

	}

	XMLStoryLoader::~XMLStoryLoader()
	{

	}

	story::StagePtr XMLStoryLoader::LoadStage( TiXmlElement* element )
	{
		story::StagePtr stage(new story::Stage());


		return stage;
	}

	story::QuestPtr XMLStoryLoader::LoadQuest( TiXmlElement* element )
	{
		story::QuestPtr quest(new story::Quest());

		return quest;
	}

	story::StoryPtr XMLStoryLoader::LoadStory( TiXmlElement* element )
	{
		story::StoryPtr story(new story::Story());

		return story;
	}

	story::StoryPtr XMLStoryLoader::LoadStory( std::string fileName )
	{
		return LoadStory(0);
	}

}