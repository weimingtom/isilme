#pragma once
#include "../Stdafx.h"
#include "../SharedCLIPtr.h"

using namespace System;
using namespace System::Collections::ObjectModel;

namespace LevelEditor
{
	namespace Proxy
	{
		public ref class ConversationProxy
		{
		public:
			ConversationProxy(story::ConversationPtr conversation);
			virtual ~ConversationProxy();

			property ObservableCollection<PhraseProxy^>^ Phrases
			{
				ObservableCollection<PhraseProxy^>^ get();
			}

			void AddPhrase(PhraseProxy^ phrase);

			void RemovePhrase(PhraseProxy^ phrase);
		private:
			ObservableCollection<PhraseProxy^>^ mPhrases;
			///< Модель диалога
			SharedCLIPtr<story::Conversation>* mConversation;
		};
	}
}
