#include "IsilmePCH.h"
#include "Conversation.h"
#include "Phrase.h"
#include "Core/MasterFile.h"
#include "Core/FactoryManager.h"
#include "Speaker.h"

namespace story
{
	Conversation::Conversation(std::string id)
	{
		mID = id;
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

	PhrasePtr Conversation::AutoChoosePhrase(SpeakerPtr speaker)
	{
		for (int i = 0; i < GetPhrasesCount(); ++i)
		{
			PhrasePtr p = GetPhrase(i);
			if (p->CheckCondition(speaker))
				return p;
		}

		return PhrasePtr();
	}

	story::ConversationPtr Conversation::Get( std::string id ) 
	{
		CategoryPtr ctg = FactoryManager::GetSingleton()->GetMasterFile()->GetCategory("Conversations");
		if (ctg)
		{
			for (int i = 0; i < ctg->GetSize(); ++i)
			{
				EntryPtr entry = ctg->GetEntry(i);
				boost::shared_ptr<ConversationEntry> ce = boost::shared_dynamic_cast<ConversationEntry>(entry);
				if (ce)
				{
					if (ce->data->GetID() == id)
						return ce->data;
				}
			}
		}
		return ConversationPtr();
	}

	void Conversation::SetID( std::string id )
	{
		mID = id;
	}

}