#include "Isilme.h"
#include "Conversation.h"
#include "Phrase.h"

namespace story
{
	Conversation::Conversation()
	{
	}

	Conversation::~Conversation()
	{
	}

	ConversationPtr Conversation::Load(TiXmlElement* convElement)
	{
		ConversationPtr conversation(new Conversation());

		// Читаем идентификатор
		const char* idAttr = convElement->Attribute("ID");
		if (idAttr)
		{
			conversation->mID = idAttr;
		}

		// Читаем фразы
		TiXmlElement* phraseElement = convElement->FirstChildElement("Phrase");
		while (phraseElement)
		{
			PhrasePtr phrase = Phrase::Load(phraseElement);
			conversation->AddPhrase(phrase);

			phraseElement = phraseElement->NextSiblingElement("Phrase");
		}

		return conversation;
	}

	void Conversation::AddPhrase(PhrasePtr phrase)
	{
		mPhrases.push_back(phrase);
	}

	int Conversation::GetPhrasesCount()
	{
		return mPhrases.size();
	}

	PhrasePtr Conversation::GetPhrase(int index)
	{
		return mPhrases.at(index);
	}

	std::string Conversation::GetID()
	{
		return mID;
	}

	PhrasePtr Conversation::AutoChoosePhrase()
	{
		for (int i = 0; i < GetPhrasesCount(); ++i)
		{
			PhrasePtr p = GetPhrase(i);
			if (p->CheckCondition())
				return p;
		}

		return PhrasePtr();
	}
}