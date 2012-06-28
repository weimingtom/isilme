//  Copyright (C) 2010-2012 VSTU
//
//	This file is part of Isilme SDK.
//
//		Isilme SDK is free software: you can redistribute it and/or modify
//		it under the terms of the GNU Lesser General Public License as published by
//		the Free Software Foundation, either version 3 of the License, or
//		(at your option) any later version.
//
//		Isilme SDK is distributed in the hope that it will be useful,
//		but WITHOUT ANY WARRANTY; without even the implied warranty of
//		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//		GNU Lesser General Public License for more details.
//
//		You should have received a copy of the GNU Lesser General Public License
//		along with Isilme SDK.  If not, see <http://www.gnu.org/licenses/>.
//
//	Этот файл — часть Isilme SDK.
//
//		Isilme SDK - свободная программа: вы можете перераспространять ее и/или
//		изменять ее на условиях Меньшей стандартной общественной лицензии GNU в том виде,
//		в каком она была опубликована Фондом свободного программного обеспечения;
//		либо версии 3 лицензии, либо (по вашему выбору) любой более поздней
//		версии.
//
//		Isilme SDK распространяется в надежде, что она будет полезной,
//		но БЕЗО ВСЯКИХ ГАРАНТИЙ; даже без неявной гарантии ТОВАРНОГО ВИДА
//		или ПРИГОДНОСТИ ДЛЯ ОПРЕДЕЛЕННЫХ ЦЕЛЕЙ. Подробнее см. в Меньшей стандартной
//		общественной лицензии GNU.
//
//		Вы должны были получить копию Меньшей стандартной общественной лицензии GNU
//		вместе с этой программой. Если это не так, см.
//		<http://www.gnu.org/licenses/>.
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