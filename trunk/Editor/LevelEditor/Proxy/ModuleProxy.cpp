#include "Stdafx.h"
#include "ModuleProxy.h"
#include "Engine/Core/MasterFile.h"
#include "../SharedCLIPtr.h"

namespace LevelEditor
{
	namespace Proxy
	{
		ObservableCollection<LevelProxy^>^ ModuleProxy::Levels::get()
		{
			return mLevels;
		}

		ObservableCollection<ConversationProxy^>^ ModuleProxy::Conversations::get()
		{
			return mConversations;
		}

		StoryProxy^ ModuleProxy::Story::get()
		{
			return mStory;
		}

		ModuleProxy::ModuleProxy(MasterFilePtr masterFile)
		{
			mMasterFile = new SharedCLIPtr<MasterFile>(masterFile);
			mCategories = gcnew ObservableCollection<CategoryProxy^>();

			// Fill all categories
			for (int i = 0; i < masterFile->GetSize(); ++i)
			{
				mCategories->Add(gcnew CategoryProxy(masterFile->GetCategoryAt(i)));
			}
		}

		ModuleProxy::~ModuleProxy()
		{
			delete mMasterFile;
		}

		ObservableCollection<CategoryProxy^>^	ModuleProxy::Categories::get()
		{
			return mCategories;
		}

		void ModuleProxy::AddLevel( LevelProxy^ level )
		{

		}

		void ModuleProxy::AddConversation( ConversationProxy^ conversation )
		{

		}

		void ModuleProxy::RemoveLevel( LevelProxy^ level )
		{

		}

		void ModuleProxy::RemoveConversation( ConversationProxy^ conversation )
		{

		}

		ModuleProxy^ ModuleProxy::Instance::get()
		{
			if (mInstance == nullptr)
				mInstance = gcnew ModuleProxy(FactoryManager::GetSingleton()->GetMasterFile());

			return mInstance;
		}

		CategoryProxy::CategoryProxy( CategoryPtr category )
		{
			mCategory = new SharedCLIPtr<Category>(category);
			mEntries = gcnew ObservableCollection<EntryProxy^>();

			// Fill entries in observable collection
			for (int i = 0; i < category->GetSize(); ++i)
			{
				mEntries->Add(gcnew EntryProxy(category->GetEntry(i)));
			}
		}

		CategoryProxy::~CategoryProxy()
		{
			delete mCategory;
		}

		ObservableCollection<EntryProxy^>^ CategoryProxy::Entries::get()
		{
			return mEntries;
		}

		String^ CategoryProxy::Name::get()
		{
			return gcnew String(mCategory->Value->GetName().c_str());
		}


		EntryProxy::EntryProxy( EntryPtr entry )
		{
			mEntry = new SharedCLIPtr<Entry>(entry);

			if (entry)
				mFilename = System::IO::Path::GetFullPath(gcnew String(mEntry->Value->GetFileName().c_str()));
		}

		EntryProxy::~EntryProxy()
		{
			delete mEntry;
		}

		String^ EntryProxy::Name::get()
		{
			return gcnew String(mEntry->Value->GetFileName().c_str());
		}

		String^ EntryProxy::FileName::get()
		{
			return mFilename;
		}
	}
}