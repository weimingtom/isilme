#include "IsilmePCH.h"
#include "ConversationSerialiser.h"

namespace serialisation
{
	XMLConversationSerialiser::XMLConversationSerialiser()
	{

	}

	XMLConversationSerialiser::~XMLConversationSerialiser()
	{

	}

	void XMLConversationSerialiser::Serilise( story::ConversationPtr conversation, std::string fileName )
	{
		TiXmlDocument document(fileName.c_str());
		TiXmlElement convElement("Conversation");

		SerialiseConversation(conversation, &convElement);
		document.InsertEndChild(convElement);

		document.SaveFile();
	}

	void XMLConversationSerialiser::SerialiseConversation( story::ConversationPtr conversation, TiXmlElement* element )
	{
		element->SetAttribute("ID", conversation->GetID().c_str());

		for (int i = 0; i < conversation->GetPhrasesCount(); ++i)
		{
			story::PhrasePtr phrase = conversation->GetPhrase(i);
			TiXmlElement phraseElement("Phrase");

			SerialisePhrase(phrase, &phraseElement);
			element->InsertEndChild(phraseElement);
		}
	}

	void XMLConversationSerialiser::SerialisePhrase( story::PhrasePtr phrase, TiXmlElement* element )
	{
		element->SetAttribute("Ref", (int)(phrase.get()));

		if (mRefs.find((int)phrase.get()) != mRefs.end())
			return;

		mRefs.insert((int)phrase.get());

		element->SetAttribute("Text", phrase->GetText().c_str());
		element->SetAttribute("Action", phrase->GetActionSource().c_str());
		element->SetAttribute("Condition", phrase->GetConditionSource().c_str());
		element->SetAttribute("Chance", phrase->GetChance());
		for (int i = 0; i < phrase->GetAnswersCount(); ++i)
		{
			story::PhrasePtr answer = phrase->GetAnswer(i);
			TiXmlElement phraseElement("Phrase");

			SerialisePhrase(answer, &phraseElement);
			element->InsertEndChild(phraseElement);
		}
	}

}