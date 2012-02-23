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

			void AddLevel(LevelProxy^ level);
			void RemoveLevel(LevelProxy^ level);
			void AddConversation(ConversationProxy^ conversation);
			void RemoveConversation(ConversationProxy^ conversation);

			property ObservableCollection<LevelProxy^>^ Levels
			{
				ObservableCollection<LevelProxy^>^ get();
			}

			property ObservableCollection<ConversationProxy^>^ Conversations
			{
				ObservableCollection<ConversationProxy^>^ get();
			}

			property StoryProxy^ Story
			{
				StoryProxy^ get();
			}
		
			/// Categories of module
			property ObservableCollection<CategoryProxy^>^ Categories
			{
				ObservableCollection<CategoryProxy^>^ get();
			}

			static property ModuleProxy^ Instance
			{
				ModuleProxy^ get();
			}
		private:
			/// Container for all game data
			SharedCLIPtr<MasterFile>* mMasterFile;

			/// Observable collection of categories
			ObservableCollection<CategoryProxy^>^ mCategories;

			ObservableCollection<LevelProxy^>^ mLevels;
			ObservableCollection<ConversationProxy^>^ mConversations;
			StoryProxy^ mStory;

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
		private:
			/// Category
			SharedCLIPtr<Category>* mCategory;

			/// Back reference to module
			ModuleProxy^ mModule;

			/// Observable collection of entries
			ObservableCollection<EntryProxy^>^ mEntries;
		};

		public ref class EntryProxy : public Common::IEditableData
		{
		public:
			EntryProxy(EntryPtr entry);
			virtual ~EntryProxy();

			/// Gets the short name of the entry
			property String^ Name
			{
				String^ get();
			}

			/// Gets the file name of the entry
			property String^ FileName
			{
				virtual String^ get();
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
		private:
			static System::Collections::Generic::Dictionary<String^, IDataToProxyConverter^>^ mConverters = gcnew System::Collections::Generic::Dictionary<String^, IDataToProxyConverter^>();;
		};
	}
}
