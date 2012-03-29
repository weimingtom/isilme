#include "IsilmePCH.h"
#include "StoryLoader.h"
#include "Core/MasterFile.h"

namespace serialisation
{


	StoryLoader::StoryLoader()
	{

	}

	StoryLoader::~StoryLoader()
	{

	}

	story::StagePtr StoryLoader::LoadStage( TiXmlElement* element )
	{
		story::StagePtr stage(new story::Stage());


		return stage;
	}

	story::QuestPtr StoryLoader::LoadQuest( TiXmlElement* element )
	{
		story::QuestPtr quest(new story::Quest());

		return quest;
	}

	story::StoryPtr StoryLoader::LoadStory( TiXmlElement* element )
	{
		story::StoryPtr story(new story::Story());

		return story;
	}

	story::StoryPtr StoryLoader::LoadStory( std::string fileName )
	{
		story::StoryPtr s(new story::Story());
		s->Load(fileName);
		return s;
	}

	EntryPtr StoryLoader::LoadEntry( std::string filename )
	{
		StoryEntry* entry = new StoryEntry(filename);
		story::StoryPtr story = LoadStory(filename);
		entry->data = story;
		return EntryPtr(entry);
	}

}