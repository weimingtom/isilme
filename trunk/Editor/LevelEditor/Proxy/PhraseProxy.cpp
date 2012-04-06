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
			mInternalID = "Phrase" + GetHashCode();
			mPhrase = new story::PhrasePtr();
			*mPhrase = phrase;
			mAnswers = gcnew ObservableCollection<PhraseProxy^>();
			isReference = phrase->IsReference();

			if (!IsReference)
			{
				for (int i = 0; i < (*mPhrase)->GetAnswersCount(); ++i)
				{
					PhraseProxy^ child = gcnew PhraseProxy((*mPhrase)->GetAnswer(i));
					mAnswers->Add(child);
					child->mParent = this;
				}
			}
		}

		PhraseProxy::PhraseProxy()
		{
			mInternalID = "Phrase" + GetHashCode();
			mPhrase = new story::PhrasePtr();
			*mPhrase = story::PhrasePtr(new story::Phrase());
			mAnswers = gcnew ObservableCollection<PhraseProxy^>();
		}

		PhraseProxy^ PhraseProxy::FindByInternalID( System::String^ id )
		{
			for each(PhraseProxy^ phrase in Answers)
			{
				if (phrase->InternalID == id)
					return phrase;
				PhraseProxy^ child = phrase->FindByInternalID(id);
				if (child != nullptr)
					return child;
			}

			return nullptr;
		}

		PhraseProxy::PhraseProxy( PhraseCopyData^ copyData )
		{
			mInternalID = "Phrase" + GetHashCode();
			mPhrase = new story::PhrasePtr();
			*mPhrase = story::PhrasePtr(new story::Phrase());
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

		PhraseProxy::PhraseProxy( PhraseProxy^ refPhrase )
		{
			mInternalID = "Phrase" + GetHashCode();
			mPhrase = new story::PhrasePtr();
			*mPhrase = story::PhrasePtr(new story::Phrase());
			(*mPhrase)->SetReference(*(refPhrase->mPhrase));
			mAnswers = gcnew ObservableCollection<PhraseProxy^>();
			mReference = refPhrase;
			isReference = true;
		}

		String^ PhraseProxy::InternalID::get()
		{
			return mInternalID;
		}

		PhraseProxy::~PhraseProxy()
		{
			delete mPhrase;
		}

		int PhraseProxy::Chance::get()
		{
			return (*mPhrase)->GetChance();
		}

		void PhraseProxy::Chance::set(int value)
		{
			(*mPhrase)->SetChance(value);
		}

		PhraseProxy^	PhraseProxy::Parent::get()
		{
			return mParent;
		}

		PhraseProxy^ PhraseProxy::Reference::get()
		{
			return mReference;
		}

		bool PhraseProxy::IsReference::get()
		{
			return (*mPhrase)->IsReference();
		}
		void PhraseProxy::AddAnswer( PhraseProxy^ answer )
		{
			(*mPhrase)->AddAnswer(*(answer->mPhrase));
			mAnswers->Add(answer);
			answer->mParent = this;
		}

		void PhraseProxy::RemoveAnswer( PhraseProxy^ answer )
		{
			(*mPhrase)->RemoveAnswer(*(answer->mPhrase));
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
			data->InternalID = InternalID;
			data->IsReference = isReference;

			if (!IsReference)
			{
				for each (PhraseProxy^ child in Answers)
				{
					data->Children->Add(child->MakeCopy());
				}
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
			return gcnew String((*mPhrase)->GetText().c_str());
		}

		void PhraseProxy::Text::set(String^ value)
		{
			(*mPhrase)->SetText((char*)Marshal::StringToHGlobalAnsi(value).ToPointer());
			RaisePropertyChanged(this, "Text");
		}

		String^ PhraseProxy::Condition::get()
		{
			return gcnew String((*mPhrase)->GetConditionSource().c_str());
		}

		void PhraseProxy::Condition::set(String^ value)
		{
		
		}

		String^ PhraseProxy::Action::get()
		{
			return gcnew String((*mPhrase)->GetActionSource().c_str());
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