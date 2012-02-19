#include "IsilmePCH.h"
#include "ConversationLoader.h"
#include "FactoryManager.h"
#include "Core/MasterFile.h"

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
		TiXmlDocument document(fileName.c_str());
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

		return conversation;
	}

	story::PhrasePtr ConversationLoader::LoadPhrase( TiXmlElement* element )
	{
		story::PhrasePtr phrase(new story::Phrase());

		int attrRef = 0;
		int attrChance = 0;

		element->QueryIntAttribute("Ref", &attrRef);
		element->QueryIntAttribute("Chance", &attrChance);
		const char* attrText = element->Attribute("Text");
		const char* attrCondition = element->Attribute("Condition");
		const char* atttrAction = element->Attribute("Action");

		story::PhrasePtr;
		if (attrRef)
		{
			phrase = GetPhraseByRef(attrRef);
			if (phrase)
			{
				phrase.reset(new story::Phrase(phrase));
				return phrase;
			}
			else
			{
				phrase.reset(new story::Phrase());
				mPhraseMap[attrRef] = phrase;
			}
		}
		else
		{
			LOG_W("Phrase has no ref uid");
			return story::PhrasePtr();	
		}

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