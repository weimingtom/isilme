#pragma once
#include "../Stdafx.h"
#include "../SharedCLIPtr.h"

using namespace System;
using namespace System::Collections::ObjectModel;

namespace LevelEditor
{
	namespace Proxy
	{
		public ref class ConversationProxy : public Common::ProxyObject
		{
		public:
			static ConversationProxy^ Load(String^ fileName);

			void SaveToFile(String^ fileName);

			ConversationProxy();
			ConversationProxy(story::ConversationPtr conversation);
			virtual ~ConversationProxy();

			property ObservableCollection<PhraseProxy^>^ Phrases
			{
				ObservableCollection<PhraseProxy^>^ get();
			}

			property String^ ID
			{
				String^ get();
				void set(String^ value);
			}

			void AddPhrase(PhraseProxy^ phrase);

			void RemovePhrase(PhraseProxy^ phrase);

			PhraseProxy^ FindByInternalID(System::String^ id);
		private:
			ObservableCollection<PhraseProxy^>^ mPhrases;
		internal:
			/// Native dialog
			story::ConversationPtr* mConversation;
		};
	}
}
