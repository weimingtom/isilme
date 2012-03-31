#pragma once 
#include "../Stdafx.h"
#include "../SharedCLIPtr.h"

using namespace System;
using namespace System::Collections::ObjectModel;

namespace LevelEditor
{
	namespace Proxy
	{
		[Serializable]
		public ref class PhraseCopyData
		{
		public:
			System::String^ Text;
			System::String^ Condition;
			System::String^ Action;
			System::Collections::Generic::List<PhraseCopyData^>^ Children;
			System::String^ InternalID;
			bool IsReference;
		};

		public ref class PhraseProxy : public Common::ProxyObject
		{
		public:
			PhraseProxy();
			PhraseProxy(story::PhrasePtr phrase);

			PhraseProxy(PhraseCopyData^ copyData);

			PhraseProxy(PhraseProxy^ refPhrase);

			PhraseCopyData^ MakeCopy();

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

			property bool IsReference
			{
				bool get();
			}

			/// Gets phrase that is referenced by
			property PhraseProxy^ Reference
			{
				PhraseProxy^ get();
			}

			[System::ComponentModel::Browsable(false)]
			property ObservableCollection<PhraseProxy^>^ Answers
			{
				ObservableCollection<PhraseProxy^>^ get();
			}

			void AddAnswer(PhraseProxy^ answer);

			void RemoveAnswer(PhraseProxy^ answer);

			[System::ComponentModel::Browsable(false)]
			property ConversationProxy^ Conversation
			{
				ConversationProxy^ get();
			}

			[System::ComponentModel::Browsable(false)]
			property PhraseProxy^ Parent
			{
				PhraseProxy^ get();
			}

			property System::String^ InternalID
			{
				System::String^ get();
			}

			PhraseProxy^	FindByInternalID(System::String^ id);
		private:
			ObservableCollection<PhraseProxy^>^ mAnswers;
			bool isReference;
		internal:
			/// An internal identifier
			System::String^ mInternalID;

			/// All phrases that refers to this instance
			System::Collections::Generic::List<PhraseProxy^>^ mRefers;
			story::PhrasePtr* mPhrase;
			ConversationProxy^ mConversation; // ?
			PhraseProxy^ mParent;
			PhraseProxy^ mReference;
		};
	}
}