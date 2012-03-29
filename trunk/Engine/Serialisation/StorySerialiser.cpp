#include "IsilmePCH.h"
#include "StorySerialiser.h"
#include "../Story/Story.h"
#include "../Story/Quest.h"
#include "../Story/Stage.h"

namespace serialisation
{


	XMLStorySerialiser::XMLStorySerialiser()
	{

	}

	XMLStorySerialiser::~XMLStorySerialiser()
	{

	}

	void XMLStorySerialiser::Serialise( story::StoryPtr story, std::string fileNmae )
	{
		TiXmlDocument document(fileNmae.c_str());

		TiXmlElement storyElement("Story");

		SerialiseStory(story, &storyElement);

		document.InsertEndChild(storyElement);
		document.SaveFile();
	}

	void XMLStorySerialiser::SerialiseStory( story::StoryPtr story, TiXmlElement* element )
	{
		for (int i = 0; i < story->GetQuestsCount(); ++i)
		{
			TiXmlElement questELement("Quest");
			SerialiseQuest(story->GetQuestAtIndex(i), &questELement);
			element->InsertEndChild(questELement);
		}
	}

	void XMLStorySerialiser::SerialiseQuest( story::QuestPtr quest, TiXmlElement* element )
	{
		element->SetAttribute("Name", quest->GetName().c_str());
		element->SetAttribute("Title", quest->GetTitle().c_str());

		for (int i = 0; i < quest->GetStageCount(); ++i)
		{
			TiXmlElement stageElement("Stage");
			SerialiseStage(quest->GetStageAtIndex(i), &stageElement);
			element->InsertEndChild(stageElement);
		}
	}

	void XMLStorySerialiser::SerialiseStage( story::StagePtr stage, TiXmlElement* element )
	{
		element->SetAttribute("ID", stage->GetID());
		element->SetAttribute("Text", stage->GetText().c_str());
		element->SetAttribute("FinishQuest", stage->IsFinishQuest() ? 1 : 0);

		TiXmlElement startScriptElement("StartScript");
		TiXmlText startScriptText("");
		startScriptText.SetCDATA(true);
		startScriptElement.InsertEndChild(startScriptText);

		TiXmlElement updateScriptElement("UpdateScript");
		TiXmlText updateScriptText("");
		updateScriptText.SetCDATA(true);
		updateScriptElement.InsertEndChild(updateScriptText);

		element->InsertEndChild(startScriptElement);
		element->InsertEndChild(updateScriptElement);
	}

}