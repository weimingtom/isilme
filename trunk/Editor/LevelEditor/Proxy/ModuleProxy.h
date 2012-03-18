#pragma once
#include "../Stdafx.h"
#include "../SharedCLIPtr.h"
#include "IDataToProxyConverter.h"

using namespace System;
using namespace System::Collections::ObjectModel;

namespace LevelEditor
{
	namespace Proxy
	{
		ref class ModuleProxy;
		ref class CategoryProxy;
		ref class EntryProxy;

		public ref class ModuleProxy
		{
		public:
			ModuleProxy(MasterFilePtr masterFile);
			virtual ~ModuleProxy();
		
			/// Categories of module
			property ObservableCollection<CategoryProxy^>^ Categories
			{
				ObservableCollection<CategoryProxy^>^ get();
			}

			static property ModuleProxy^ Instance
			{
				ModuleProxy^ get();
			}

			/// Gets category with name 
			/// returns category or null
			CategoryProxy^ GetCategory(String^ Name);
		internal:
			/// Container for all game data
			SharedCLIPtr<MasterFile>* mMasterFile;

		private:
			/// Observable collection of categories
			ObservableCollection<CategoryProxy^>^ mCategories;

			/// Instance of module
			static ModuleProxy^ mInstance;
		};

		public ref class CategoryProxy
		{
		public:
			CategoryProxy(CategoryPtr category);
			virtual ~CategoryProxy();

			/// Gets collection of entries in category
			property ObservableCollection<EntryProxy^>^ Entries
			{
				ObservableCollection<EntryProxy^>^ get();
			}

			/// Gets name of the category
			property String^ Name
			{
				String^ get();
			}

			/// Gets or sets default extension for files
			property System::String^ FileExtension
			{
				System::String^ get();
				void set(System::String^ value);
			}

			/// Get or sets image source for icon in category
			property System::Windows::Media::ImageSource^ Icon
			{
				System::Windows::Media::ImageSource^ get();
				void set(System::Windows::Media::ImageSource^ value);
			}

			/// Gets or sets converter from native data to editable proxy object
			property IDataToProxyConverter^ Converter
			{
				IDataToProxyConverter^ get();
				void set(IDataToProxyConverter^ value);
			}

			/// Gets or sets factory for new entries in category
			property IEntryFactory^ Factory
			{
				IEntryFactory^ get();
				void set(IEntryFactory^ value);
			}

			/// Adds entry to category
			void AddEntry(EntryProxy^ entry);

			/// Removes entry from the category
			void RemoveEntry(EntryProxy^ entry);
		internal:
			/// Category
			SharedCLIPtr<Category>* mCategory;

		private:
			/// Back reference to module
			ModuleProxy^ mModule;

			/// Observable collection of entries
			ObservableCollection<EntryProxy^>^ mEntries;

			IDataToProxyConverter^ mConverter;

			IEntryFactory^ mFactory;

			/// Icon 
			System::Windows::Media::ImageSource^ mIcon;

			/// Default file extension
			System::String^ mFileExtension;
		};

		public ref class EntryProxy : public Common::IEditableData
		{
		public:
			EntryProxy(EntryPtr entry);
			virtual ~EntryProxy();

			/// Gets or sets the short name of the entry
			property String^ Name
			{
				String^ get();
				void set(String^ value);
			}

			/// Gets the file name of the entry
			property String^ FileName
			{
				virtual String^ get();
				void set(String^ value);
			}

			property Common::IProxyObject^ Data
			{
				virtual Common::IProxyObject^ get();
			}

			property CategoryProxy^ Category
			{
				CategoryProxy^ get();
			}

			property String^ EditorTag
			{
				virtual String^ get();
			}
		internal:
			/// Entry container
			SharedCLIPtr<Entry>* mEntry;

			/// Back reference to category
			CategoryProxy^ mCategory;

			/// Editable data
			Common::IProxyObject^ mData;
		private:
			/// Absolute file name
			String^ mFilename;
		};

		public ref class LevelDataToProxyConverter : public IDataToProxyConverter
		{
		public:
			LevelDataToProxyConverter();
			virtual Common::IProxyObject^ Convert(SharedCLIPtr<Entry>* entry) override;
		};

		public ref class GameDataToProxyConverter
		{
		public:
			/// Converts entry data to the proxy object for editor
			static Common::IProxyObject^ Convert(SharedCLIPtr<Entry>* entry, String^ category);

			static Common::IProxyObject^ Convert(EntryProxy^ entry, String^ category);

			/// Registers converter for data
			static void RegisterConverter(String^ category, IDataToProxyConverter^ comverter);

			/// Gets converter for category
			static IDataToProxyConverter^ GetConverter(String^ category);

			/// Registers factory for entry
			static void RegisterFactory(String^ category, IEntryFactory^ factory);

			/// Creates new item for category
			static EntryProxy^	CreateNewEntry(String^ category);
		private:
			static System::Collections::Generic::Dictionary<String^, IDataToProxyConverter^>^ mConverters = gcnew System::Collections::Generic::Dictionary<String^, IDataToProxyConverter^>();
			static System::Collections::Generic::Dictionary<String^, IEntryFactory^>^ mFactories = gcnew System::Collections::Generic::Dictionary<String^, IEntryFactory^>();
		};
	}
}
