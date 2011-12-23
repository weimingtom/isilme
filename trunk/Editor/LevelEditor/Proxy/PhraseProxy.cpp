#include "Stdafx.h"
#include "PhraseProxy.h"
#include "ConversationProxy.h"

namespace LevelEditor
{
	namespace Proxy
	{
	

		PhraseProxy::PhraseProxy( story::PhrasePtr phrase )
		{
			mPhrase = new SharedCLIPtr<story::Phrase>(phrase);
			mAnswers = gcnew ObservableCollection<PhraseProxy^>();
		}

		PhraseProxy::~PhraseProxy()
		{

		}

		void PhraseProxy::AddAnswer( PhraseProxy^ answer )
		{

		}

		void PhraseProxy::RemoveAnswer( PhraseProxy^ answer )
		{

		}

		ObservableCollection<PhraseProxy^>^ PhraseProxy::Answers::get()
		{
			return mAnswers;
		}

		String^ PhraseProxy::Text::get()
		{
			return gcnew String(mPhrase->Value->GetText().c_str());
		}

		void PhraseProxy::Text::set(String^ value)
		{
		
		}

		String^ PhraseProxy::Condition::get()
		{
			return "";
		}

		void PhraseProxy::Condition::set(String^ value)
		{
		
		}

		String^ PhraseProxy::Action::get()
		{
			return "";
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