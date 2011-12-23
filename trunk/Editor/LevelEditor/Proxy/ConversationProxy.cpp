#include "Stdafx.h"
#include "ConversationProxy.h"

namespace LevelEditor
{
	namespace Proxy
	{
	

		ConversationProxy::ConversationProxy( story::ConversationPtr conversation )
		{
			mConversation = new SharedCLIPtr<story::Conversation>(conversation);
			mPhrases = gcnew ObservableCollection<PhraseProxy^>();
		}

		ConversationProxy::~ConversationProxy()
		{
			delete mConversation;
		}

		void ConversationProxy::AddPhrase( PhraseProxy^ phrase )
		{

		}

		void ConversationProxy::RemovePhrase( PhraseProxy^ phrase )
		{

		}

		ObservableCollection<PhraseProxy^>^ ConversationProxy::Phrases::get()
		{
			return mPhrases;
		}
	}
}