#include "IsilmePCH.h"
#include "ConversationLoader.h"

namespace serialisation
{


	XMLConversationLoader::XMLConversationLoader()
	{

	}

	XMLConversationLoader::~XMLConversationLoader()
	{

	}

	story::ConversationPtr XMLConversationLoader::LoadConversation( std::string fileName )
	{
		TiXmlDocument document(fileName.c_str());
		document.LoadFile();

		if (document.RootElement())
			return LoadConversation(document.RootElement());

		return story::ConversationPtr();
	}

	story::ConversationPtr XMLConversationLoader::LoadConversation( TiXmlElement* element )
	{
		mPhraseMap.clear();
		story::ConversationPtr conversation(new story::Conversation());

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

	story::PhrasePtr XMLConversationLoader::LoadPhrase( TiXmlElement* element )
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

	story::PhrasePtr XMLConversationLoader::GetPhraseByRef( int refValue )
	{
		if (mPhraseMap.find(refValue) != mPhraseMap.end())
			return mPhraseMap[refValue];
		else 
			return story::PhrasePtr();
	}

}