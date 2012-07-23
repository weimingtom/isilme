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
#include "ConversationLoader.h"
#include "Core/FactoryManager.h"
#include "Core/MasterFile.h"
#include "../Core/Engine.h"
#include "../Core/ResourceManager.h"

namespace serialisation
{


	ConversationLoader::ConversationLoader()
	{

	}

	ConversationLoader::~ConversationLoader()
	{

	}

	story::ConversationPtr ConversationLoader::LoadConversation( std::string fileName )
	{
        char* path = Engine::GetSingleton()->GetResourceManager()->ResourcePath(fileName.c_str());
		TiXmlDocument document(path);
		document.LoadFile();

		if (document.RootElement())
			return LoadConversation(document.RootElement());

		return story::ConversationPtr();
	}

	story::ConversationPtr ConversationLoader::LoadConversation( TiXmlElement* element )
	{
		mPhraseMap.clear();

		const char* idAttr = element->Attribute("ID");
		if (!idAttr)
		{
			LOG_W("Conversation has no ID!");
			return story::ConversationPtr();
		}

		story::ConversationPtr conversation(new story::Conversation(idAttr));
	//	FactoryManager::GetSingleton()->AddConversation(conversation);

		TiXmlElement* phraseElement = element->FirstChildElement("Phrase");
		while (phraseElement)
		{
			story::PhrasePtr phrase = LoadPhrase(phraseElement);
			if (phrase)
				conversation->AddPhrase(phrase);

			phraseElement = phraseElement->NextSiblingElement("Phrase");
		}

		// Set references
		for (PhraseRefMap::iterator it = mRefMap.begin(); it != mRefMap.end(); ++it)
		{
			story::PhrasePtr refPhrase = mPhraseMap[it->second];
			if (refPhrase)
			{
				it->first->SetReference(refPhrase);
			}
			else
			{
				LOG_W("There is no phrase for %d id", it->second);
			}
		}
		return conversation;
	}

	story::PhrasePtr ConversationLoader::LoadPhrase( TiXmlElement* element )
	{
		story::PhrasePtr phrase(new story::Phrase());

		int attrRef = 0;
		int attrChance = 0;

		if (element->Attribute("Ref") != nullptr)
		{
			element->QueryIntAttribute("Ref", &attrRef);
			mRefMap[phrase] = attrRef;
		}
		else if (element->Attribute("ID") != nullptr)
		{
			element->QueryIntAttribute("ID", &attrRef);
			mPhraseMap[attrRef] = phrase;

			element->QueryIntAttribute("Chance", &attrChance);
			const char* attrText = element->Attribute("Text");
			const char* attrCondition = element->Attribute("Condition");
			const char* atttrAction = element->Attribute("Action");

			if (attrText)
				phrase->SetText(attrText);

			if (attrCondition)
				phrase->SetCondition(attrCondition);

			if (atttrAction)
				phrase->SetAction(atttrAction);

			if (attrChance)
				phrase->SetChance(attrChance);

			TiXmlElement* answerElement = element->FirstChildElement("Phrase");
			while (answerElement)
			{
				story::PhrasePtr answer = LoadPhrase(answerElement);
				if (answer)
					phrase->AddAnswer(answer);

				answerElement = answerElement->NextSiblingElement("Phrase");
			}
		}

		return phrase;
	}

	story::PhrasePtr ConversationLoader::GetPhraseByRef( int refValue )
	{
		if (mPhraseMap.find(refValue) != mPhraseMap.end())
			return mPhraseMap[refValue];
		else 
			return story::PhrasePtr();
	}

	EntryPtr ConversationLoader::LoadEntry( std::string filename )
	{
		ConversationEntry* entry = new ConversationEntry(filename);
		story::ConversationPtr conversation = LoadConversation(filename);
		entry->data = conversation;
		return EntryPtr(entry);
	}

}