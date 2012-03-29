#pragma once

#include "../Stdafx.h"
#include "../Proxy/ScriptFileProxy.h"

namespace LevelEditor
{
	namespace View
	{
		public ref class QuestEditorWindow : public Common::Views::EditorWindow
		{
		public:
			static System::Windows::Input::RoutedCommand^ AddQuest = gcnew System::Windows::Input::RoutedCommand();
			static System::Windows::Input::RoutedCommand^ AddStage = gcnew System::Windows::Input::RoutedCommand();

			QuestEditorWindow();

			virtual void Load(Common::IEditableData^ data) override;

			virtual void Load() override;

			virtual void Save() override;
		protected:
			void ExecutedCopy(System::Object^ sender, System::Windows::Input::ExecutedRoutedEventArgs^ e);
			void CanExecuteCopy(System::Object^ sender, System::Windows::Input::CanExecuteRoutedEventArgs^ e);

			void ExecutedCut(System::Object^ sender, System::Windows::Input::ExecutedRoutedEventArgs^ e);
			void CanExecuteCut(System::Object^ sender, System::Windows::Input::CanExecuteRoutedEventArgs^ e);

			void ExecutedPaste(System::Object^ sender, System::Windows::Input::ExecutedRoutedEventArgs^ e);
			void CanExecutePaste(System::Object^ sender, System::Windows::Input::CanExecuteRoutedEventArgs^ e);

			void ExecutedAddQuest(System::Object^ sender, System::Windows::Input::ExecutedRoutedEventArgs^ e);
			void CanExecuteAddQuest(System::Object^ sender, System::Windows::Input::CanExecuteRoutedEventArgs^ e);

			void ExecutedAddStage(System::Object^ sender, System::Windows::Input::ExecutedRoutedEventArgs^ e);
			void CanExecuteAddStage(System::Object^ sender, System::Windows::Input::CanExecuteRoutedEventArgs^ e);

			void ExecutedDelete(System::Object^ sender, System::Windows::Input::ExecutedRoutedEventArgs^ e);
			void CanExecuteDelete(System::Object^ sender, System::Windows::Input::CanExecuteRoutedEventArgs^ e);

			void OnStoryTree_SelectedItemChanged( System::Object^ sender, System::Windows::RoutedPropertyChangedEventArgs<Object^>^ e );
		private:
			/// Story
			Proxy::StoryProxy^ mStory;

			/// StoryTree
			System::Windows::Controls::TreeView^ mStoryTree;
		};

		public ref class QuestEditorToolBar : public System::Windows::Controls::ToolBar
		{
		public:
			QuestEditorToolBar();

			static property QuestEditorToolBar^ Instance
			{
				QuestEditorToolBar^ get();
			}
		private:
			static QuestEditorToolBar^ mInstance = nullptr;
		};
	}
}