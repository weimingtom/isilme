#include "Stdafx.h"
#include "PhraseProxy.h"
#include "ConversationProxy.h"

using namespace System::Runtime::InteropServices;
using namespace System;
using namespace System::Collections::Generic;

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
					child->mParent = this;
				}
			}
		}

		PhraseProxy::PhraseProxy()
		{
			mPhrase = new SharedCLIPtr<story::Phrase>(story::PhrasePtr(new story::Phrase()));
			mAnswers = gcnew ObservableCollection<PhraseProxy^>();
		}

		PhraseProxy::PhraseProxy( PhraseCopyData^ copyData )
		{
			mPhrase = new SharedCLIPtr<story::Phrase>(story::PhrasePtr(new story::Phrase()));
			mAnswers = gcnew ObservableCollection<PhraseProxy^>();

			Text = copyData->Text;
			Condition = copyData->Condition;
			Action = copyData->Action;

			for each (PhraseCopyData^ child in copyData->Children)
			{
				PhraseProxy^ answer = gcnew PhraseProxy(child);
				AddAnswer(answer);
			}
		}

		PhraseProxy::~PhraseProxy()
		{

		}

		PhraseProxy^	PhraseProxy::Parent::get()
		{
			return mParent;
		}

		bool PhraseProxy::IsReference::get()
		{
			return mPhrase->Value->IsReference();
		}
		void PhraseProxy::AddAnswer( PhraseProxy^ answer )
		{
			mPhrase->Value->AddAnswer(answer->mPhrase->Value);
			mAnswers->Add(answer);
			answer->mParent = this;
		}

		void PhraseProxy::RemoveAnswer( PhraseProxy^ answer )
		{
			mPhrase->Value->RemoveAnswer(answer->mPhrase->Value);
			answer->mParent = nullptr;
			mAnswers->Remove(answer);
		}

		PhraseCopyData^ PhraseProxy::MakeCopy()
		{
			PhraseCopyData^ data = gcnew PhraseCopyData();
			data->Text = Text;
			data->Condition = Condition;
			data->Action = Action;
			data->Children = gcnew List<PhraseCopyData^>();

			if (!IsReference)
			{
				for each (PhraseProxy^ child in Answers)
				{
					data->Children->Add(child->MakeCopy());
				}
			}
			else
			{
			}

			return data;
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
			if (mConversation == nullptr)
				return Parent->Conversation;
			else
				return mConversation;
		}
	}
}