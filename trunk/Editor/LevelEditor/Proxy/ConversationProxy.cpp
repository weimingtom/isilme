#include "Stdafx.h"
#include "ConversationProxy.h"
#include "Engine/Serialisation/ConversationSerialiser.h"
#include "Engine/Serialisation/ConversationLoader.h"
#include "PhraseProxy.h"
#include "Engine/Core/MasterFile.h"

using namespace System::Runtime::InteropServices;

namespace LevelEditor
{
	namespace Proxy
	{
		ConversationProxy::ConversationProxy( story::ConversationPtr conversation )
		{
			mConversation = new SharedCLIPtr<story::Conversation>(conversation);
			mPhrases = gcnew ObservableCollection<PhraseProxy^>();

			if (!mConversation->Value)
				mConversation->Value.reset(new story::Conversation(""));

			for (int i = 0; i < mConversation->Value->GetPhrasesCount(); ++i)
			{
				PhraseProxy^ phrase = gcnew PhraseProxy(mConversation->Value->GetPhrase(i));
				phrase->mConversation = this;

				mPhrases->Add(phrase);
			}
		}

		ConversationProxy::ConversationProxy()
		{
			mConversation = new SharedCLIPtr<story::Conversation>(story::ConversationPtr(new story::Conversation("")));
			mPhrases = gcnew ObservableCollection<PhraseProxy^>();
		}

		ConversationProxy::~ConversationProxy()
		{
			delete mConversation;
		}

		void ConversationProxy::AddPhrase( PhraseProxy^ phrase )
		{
			mConversation->Value->AddPhrase(phrase->mPhrase->Value);
			mPhrases->Add(phrase);
			phrase->mConversation = this;
		}

		void ConversationProxy::RemovePhrase( PhraseProxy^ phrase )
		{
			//mConversation->Value->RemovePhrase(phrase->mPhrase->Value);
			mPhrases->Remove(phrase);
			phrase->mConversation = nullptr;
		}

		ConversationProxy^ ConversationProxy::Load( String^ fileName )
		{
			serialisation::ConversationLoader loader;

			MasterFilePtr mf = FactoryManager::GetSingleton()->GetMasterFile();
			CategoryPtr lc = mf->GetCategory("Levels");
			std::string fn = static_cast<char*>(Marshal::StringToHGlobalAnsi(fileName->ToLower()).ToPointer());
			story::ConversationPtr conv;
			for (int i = 0; i < lc->GetSize(); ++i)
			{
				String^ fullPath = System::IO::Path::GetFullPath(gcnew String(lc->GetEntry(i)->GetFileName().c_str()))->ToLower();
				std::string fp = static_cast<char*>(Marshal::StringToHGlobalAnsi(fullPath).ToPointer());

				if (fn == fp)
				{
					conv = lc->GetEntry<ContainerEntry<story::Conversation> >(i)->data;
					break;
				}
			}
			ConversationProxy^ conversation = gcnew ConversationProxy(conv);
			return conversation;
		}

		void ConversationProxy::SaveToFile( String^ fileName )
		{
			serialisation::XMLConversationSerialiser serialiser;

			serialiser.Serilise(mConversation->Value, (char*)Marshal::StringToHGlobalAnsi(fileName).ToPointer());
		}

		ObservableCollection<PhraseProxy^>^ ConversationProxy::Phrases::get()
		{
			return mPhrases;
		}

		String^ ConversationProxy::ID::get()
		{
			return gcnew String(mConversation->Value->GetID().c_str());
		}

		void ConversationProxy::ID::set(String^ value)
		{
			
		}
	}
}