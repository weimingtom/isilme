#include "Stdafx.h"
#include "ConversationProxy.h"
#include "Engine/Serialisation/ConversationSerialiser.h"
#include "Engine/Serialisation/ConversationLoader.h"
#include "PhraseProxy.h"
#include "Engine/Core/MasterFile.h"
#include "../ResourceHelper.h"

using namespace System::Runtime::InteropServices;

namespace LevelEditor
{
	namespace Proxy
	{
		ConversationProxy::ConversationProxy( story::ConversationPtr conversation )
		{
			mConversation = new story::ConversationPtr();
			*mConversation = conversation;
			mPhrases = gcnew ObservableCollection<PhraseProxy^>();

			if ((*mConversation) == nullptr)
				(*mConversation).reset(new story::Conversation(""));

			for (int i = 0; i < (*mConversation)->GetPhrasesCount(); ++i)
			{
				PhraseProxy^ phrase = gcnew PhraseProxy((*mConversation)->GetPhrase(i));
				phrase->mConversation = this;

				mPhrases->Add(phrase);
			}
		}

		ConversationProxy::ConversationProxy()
		{
			mConversation = new story::ConversationPtr();
			*mConversation = story::ConversationPtr(new story::Conversation(""));
			mPhrases = gcnew ObservableCollection<PhraseProxy^>();
		}

		ConversationProxy::~ConversationProxy()
		{
			delete mConversation;
		}

		void ConversationProxy::AddPhrase( PhraseProxy^ phrase )
		{
			(*mConversation)->AddPhrase(*phrase->mPhrase);
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

			serialiser.Serilise(*mConversation, (char*)Marshal::StringToHGlobalAnsi(fileName).ToPointer());
		}

		PhraseProxy^ ConversationProxy::FindByInternalID( System::String^ id )
		{
			for each(PhraseProxy^ phrase in mPhrases)
			{
				if (phrase->InternalID == id)
					return phrase;
				PhraseProxy^ child = phrase->FindByInternalID(id);
				if (child != nullptr)
					return child;
			}
			return nullptr;
		}

		ObservableCollection<PhraseProxy^>^ ConversationProxy::Phrases::get()
		{
			return mPhrases;
		}

		String^ ConversationProxy::ID::get()
		{
			return gcnew String((*mConversation)->GetID().c_str());
		}

		void ConversationProxy::ID::set(String^ value)
		{
			(*mConversation)->SetID(ResourceHelper::StringToChar(value));
		}
	}
}