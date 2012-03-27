#include "Stdafx.h"
#include "ModuleProxy.h"
#include "Engine/Core/MasterFile.h"
#include "../SharedCLIPtr.h"
#include "LevelProxy.h"
#include "IEntryFactory.h"
#include "IDataToProxyConverter.h"
#include "ConversationProxy.h"

namespace LevelEditor
{
	namespace Proxy
	{
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

		CategoryProxy^ ModuleProxy::GetCategory( String^ name )
		{
			for each (CategoryProxy^ ctg in mCategories)
				if (ctg->Name == name)
					return ctg;

			return nullptr;
		}

		ObservableCollection<CategoryProxy^>^	ModuleProxy::Categories::get()
		{
			return mCategories;
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
				EntryProxy^ entry = gcnew EntryProxy(category->GetEntry(i));
				entry->mCategory = this;
				mEntries->Add(entry);
			}

			mFileExtension = "";
		}

		CategoryProxy::~CategoryProxy()
		{
			delete mCategory;
		}

		void CategoryProxy::AddEntry( EntryProxy^ entry )
		{
			mEntries->Add(entry);
			entry->mCategory = this;
			mCategory->Value->Add(entry->mEntry->Value);
		}

		void CategoryProxy::RemoveEntry( EntryProxy^ entry )
		{
			mEntries->Remove(entry);
			entry->mCategory = nullptr;
			mCategory->Value->Remove(entry->mEntry->Value);
		}

		ObservableCollection<EntryProxy^>^ CategoryProxy::Entries::get()
		{
			return mEntries;
		}

		String^ CategoryProxy::Name::get()
		{
			return gcnew String(mCategory->Value->GetName().c_str());
		}

		System::Windows::Media::ImageSource^ CategoryProxy::Icon::get()
		{
			return mIcon;
		}

		void CategoryProxy::Icon::set(System::Windows::Media::ImageSource^ value)
		{
			mIcon = value;
		}

		String^ CategoryProxy::FileExtension::get()
		{
			return mFileExtension;
		}

		void CategoryProxy::FileExtension::set(String^ value)
		{
			mFileExtension = value;
		}

		IEntryFactory^ CategoryProxy::Factory::get()
		{
			return mFactory;
		}

		void CategoryProxy::Factory::set(IEntryFactory^ value)
		{
			mFactory = value;
		}

		IDataToProxyConverter^ CategoryProxy::Converter::get()
		{
			return mConverter;
		}

		void CategoryProxy::Converter::set(IDataToProxyConverter^ value)
		{
			mConverter = value;
		}

		EntryProxy::EntryProxy( EntryPtr entry )
		{
			mEntry = new SharedCLIPtr<Entry>(entry);

			if (entry && mEntry->Value->GetFileName() != "")
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

		void EntryProxy::Name::set(String^ value)
		{
		}

		void EntryProxy::FileName::set(String^ value)
		{
			mFilename = value;
			mEntry->Value->SetFileName((char*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(mFilename).ToPointer());
		}

		String^ EntryProxy::FileName::get()
		{
			return mFilename;
		}

		Common::IProxyObject^ EntryProxy::Data::get()
		{
			if (mData == nullptr)
			{
				IDataToProxyConverter^ converter = Category->Converter;
				if (converter != nullptr)
					mData = converter->Convert(mEntry);
			}

			return mData;
		}

		CategoryProxy^ EntryProxy::Category::get()
		{
			return mCategory;
		}

		String^ EntryProxy::EditorTag::get()
		{
			return mCategory->Name;
		}
		Common::IProxyObject^ GameDataToProxyConverter::Convert( SharedCLIPtr<Entry>* entry, String^ category )
		{
			IDataToProxyConverter^ converter = GetConverter(category);
			if (converter != nullptr)
				return converter->Convert(entry);

			return nullptr;
		}

		Common::IProxyObject^ GameDataToProxyConverter::Convert( EntryProxy^ entry, String^ category )
		{
			return Convert(entry->mEntry, category);
		}

		IDataToProxyConverter^ GameDataToProxyConverter::GetConverter( String^ category )
		{
			if (mConverters->ContainsKey(category))
				return mConverters[category];

			return nullptr;
		}

		void GameDataToProxyConverter::RegisterConverter( String^ category, IDataToProxyConverter^ comverter )
		{
			mConverters[category] = comverter;
		}

		void GameDataToProxyConverter::RegisterFactory( String^ category, IEntryFactory^ factory )
		{
			mFactories[category] = factory;
		}

		EntryProxy^ GameDataToProxyConverter::CreateNewEntry( String^ category )
		{
			if (mFactories->ContainsKey(category))
				return mFactories[category]->CreateNewEntry();

			return nullptr;
		}

		LevelDataToProxyConverter::LevelDataToProxyConverter()
		{

		}

		Common::IProxyObject^ LevelDataToProxyConverter::Convert( SharedCLIPtr<Entry>* entry )
		{
			boost::shared_ptr<LevelEntry> le = boost::shared_dynamic_cast<LevelEntry>(entry->Value);
			
			if (!le)
				return nullptr;

			LevelPtr lvl = le->data;
			LevelProxy^ level = gcnew LevelProxy(lvl);
			return level;
		}

		ConversationDataToProxyConverter::ConversationDataToProxyConverter()
		{

		}

		Common::IProxyObject^ ConversationDataToProxyConverter::Convert( SharedCLIPtr<Entry>* entry )
		{
			boost::shared_ptr<ConversationEntry> ce = boost::shared_dynamic_cast<ConversationEntry>(entry->Value);

			if (!ce)
				return nullptr;

			story::ConversationPtr conv = ce->data;
			ConversationProxy^ proxy = gcnew ConversationProxy(conv);
			return proxy;
		}

	}
}