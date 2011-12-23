#pragma once 
#include "../Stdafx.h"
#include "../SharedCLIPtr.h"

using namespace System;
using namespace System::Collections::ObjectModel;
namespace LevelEditor
{
	namespace Proxy
	{
		public ref class PhraseProxy : public Common::ProxyObject
		{
		public:
			PhraseProxy(story::PhrasePtr phrase);
			virtual ~PhraseProxy();

			property String^ Text
			{
				String^ get();
				void set(String^ value);
			}

			property String^ Condition
			{
				String^ get();
				void set(String^ value);
			}

			property String^ Action
			{
				String^ get();
				void set(String^ value);
			}

			property ObservableCollection<PhraseProxy^>^ Answers
			{
				ObservableCollection<PhraseProxy^>^ get();
			}

			void AddAnswer(PhraseProxy^ answer);

			void RemoveAnswer(PhraseProxy^ answer);

			property ConversationProxy^ Conversation
			{
				ConversationProxy^ get();
			}
		private:
			SharedCLIPtr<story::Phrase>* mPhrase;
			ObservableCollection<PhraseProxy^>^ mAnswers;
		internal:
			ConversationProxy^ mConversation; // ?
		};
	}
}