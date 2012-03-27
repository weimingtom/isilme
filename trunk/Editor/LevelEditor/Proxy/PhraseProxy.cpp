#include "Stdafx.h"
#include "PhraseProxy.h"
#include "ConversationProxy.h"

using namespace System::Runtime::InteropServices;

namespace LevelEditor
{
	namespace Proxy
	{
	

		PhraseProxy::PhraseProxy( story::PhrasePtr phrase )
		{
			mPhrase = new SharedCLIPtr<story::Phrase>(phrase);
			mAnswers = gcnew ObservableCollection<PhraseProxy^>();
			isReference = phrase->IsReference();

			if (!IsReference)
			{
				for (int i = 0; i < mPhrase->Value->GetAnswersCount(); ++i)
				{
					PhraseProxy^ child = gcnew PhraseProxy(mPhrase->Value->GetAnswer(i));
					mAnswers->Add(child);
				}
			}
		}

		PhraseProxy::PhraseProxy()
		{
			mPhrase = new SharedCLIPtr<story::Phrase>(story::PhrasePtr(new story::Phrase()));
			mAnswers = gcnew ObservableCollection<PhraseProxy^>();
		}

		PhraseProxy::~PhraseProxy()
		{

		}

		bool PhraseProxy::IsReference::get()
		{
			return mPhrase->Value->IsReference();
		}
		void PhraseProxy::AddAnswer( PhraseProxy^ answer )
		{
			mPhrase->Value->AddAnswer(answer->mPhrase->Value);
			mAnswers->Add(answer);
		}

		void PhraseProxy::RemoveAnswer( PhraseProxy^ answer )
		{
			//mPhrase->Value->RemoveAnswer(answer->mPhrase->Value);
			mAnswers->Remove(answer);
		}

		ObservableCollection<PhraseProxy^>^ PhraseProxy::Answers::get()
		{
			if (isReference)
				return nullptr;

			return mAnswers;
		}

		String^ PhraseProxy::Text::get()
		{
			return gcnew String(mPhrase->Value->GetText().c_str());
		}

		void PhraseProxy::Text::set(String^ value)
		{
			mPhrase->Value->SetText((char*)Marshal::StringToHGlobalAnsi(value).ToPointer());
			RaisePropertyChanged(this, "Text");
		}

		String^ PhraseProxy::Condition::get()
		{
			return gcnew String(mPhrase->Value->GetConditionSource().c_str());
		}

		void PhraseProxy::Condition::set(String^ value)
		{
		
		}

		String^ PhraseProxy::Action::get()
		{
			return gcnew String(mPhrase->Value->GetActionSource().c_str());
		}

		void PhraseProxy::Action::set(String^ value)
		{
			
		}

		ConversationProxy^	PhraseProxy::Conversation::get()
		{
			return mConversation;
		}
	}
}