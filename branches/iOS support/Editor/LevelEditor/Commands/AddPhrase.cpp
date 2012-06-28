#include "Stdafx.h"
#include "AddPhrase.h"
#include "../Proxy/ConversationProxy.h"
#include "../Proxy/PhraseProxy.h"

namespace LevelEditor
{
	namespace Commands
	{
	

		AddPhrase::AddPhrase( ConversationProxy^ conversation, PhraseProxy^ phrase )
		{
			mConversation = conversation;
			mPhrase = phrase;
		}

		AddPhrase::AddPhrase( PhraseProxy^ parent, PhraseProxy^ child )
		{
			mParentPhrase = parent;
			mPhrase = child;
		}

		void AddPhrase::Execute()
		{
			if (mConversation != nullptr)
				mConversation->AddPhrase(mPhrase);
			else
				mParentPhrase->AddAnswer(mPhrase);
		}

		void AddPhrase::Unexecute()
		{
			if (mConversation != nullptr)
				mConversation->RemovePhrase(mPhrase);
			else
				mParentPhrase->RemoveAnswer(mPhrase);
		}

	}
}