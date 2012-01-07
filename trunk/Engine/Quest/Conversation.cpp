#include "IsilmePCH.h"
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

	PhrasePtr Conversation::AutoChoosePhrase(EntityPtr speaker)
	{
		for (int i = 0; i < GetPhrasesCount(); ++i)
		{
			PhrasePtr p = GetPhrase(i);
			if (p->CheckCondition(speaker))
				return p;
		}

		return PhrasePtr();
	}
}