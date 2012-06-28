#include "Stdafx.h"
#include "RemovePhrase.h"
#include "../Proxy/ConversationProxy.h"
#include "../Proxy/PhraseProxy.h"

namespace LevelEditor
{
	namespace Commands
	{
	

		RemovePhrase::RemovePhrase( PhraseProxy^ phrase )
		{
			mConversation = phrase->Conversation;
			mPhrase = phrase;
			mParentPhrase = phrase->Parent;
		}

		void RemovePhrase::Execute()
		{
			if (mParentPhrase != nullptr)
				mParentPhrase->RemoveAnswer(mPhrase);
			else
				mConversation->RemovePhrase(mPhrase);
		}

		void RemovePhrase::Unexecute()
		{
			if (mParentPhrase != nullptr)
				mParentPhrase->AddAnswer(mPhrase);
			else
				mConversation->AddPhrase(mPhrase);
		}

	}
}