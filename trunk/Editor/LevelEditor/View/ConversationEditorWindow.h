#pragma once

#include "../Stdafx.h"

namespace LevelEditor
{
	namespace View
	{
		public ref class ConversationEditorWindow : public Common::Views::EditorWindow
		{
		public:
			static System::Windows::Input::RoutedCommand^ AddPhraseCommand = gcnew System::Windows::Input::RoutedCommand();
			static System::Windows::Input::RoutedCommand^ PasteRefCommand = gcnew System::Windows::Input::RoutedCommand();

			ConversationEditorWindow();

			virtual void Load(Common::IEditableData^ data) override;

			virtual void Save() override;
		private:
			void ExecutedCopy(System::Object^ sender, System::Windows::Input::ExecutedRoutedEventArgs^ e);
			void CanExecuteCopy(System::Object^ sender, System::Windows::Input::CanExecuteRoutedEventArgs^ e);

			void ExecutedCut(System::Object^ sender, System::Windows::Input::ExecutedRoutedEventArgs^ e);
			void CanExecuteCut(System::Object^ sender, System::Windows::Input::CanExecuteRoutedEventArgs^ e);

			void ExecutedPaste(System::Object^ sender, System::Windows::Input::ExecutedRoutedEventArgs^ e);
			void CanExecutePaste(System::Object^ sender, System::Windows::Input::CanExecuteRoutedEventArgs^ e);

			void ExecutedAddPhrase(System::Object^ sender, System::Windows::Input::ExecutedRoutedEventArgs^ e);
			void CanExecuteAddPhrase(System::Object^ sender, System::Windows::Input::CanExecuteRoutedEventArgs^ e);

			void ExecutedPasteRef(System::Object^ sender, System::Windows::Input::ExecutedRoutedEventArgs^ e);
			void CanExecutePasteRef(System::Object^ sender, System::Windows::Input::CanExecuteRoutedEventArgs^ e);

			void ExecutedDelete(System::Object^ sender, System::Windows::Input::ExecutedRoutedEventArgs^ e);
			void CanExecuteDelete(System::Object^ sender, System::Windows::Input::CanExecuteRoutedEventArgs^ e);

			void OnDialogTree_SelectedItemChanged(System::Object^ sender, System::Windows::RoutedPropertyChangedEventArgs<Object^>^ e);
			
			/// Dialog tree
			System::Windows::Controls::TreeView^	mDialogTree;

			/// Conversation for editing
			Proxy::ConversationProxy^ mConversation;
		};

		public ref class ConversationEditorToolBar : public System::Windows::Controls::ToolBar
		{
		public:
			ConversationEditorToolBar();

			static property ConversationEditorToolBar^ Instance
			{
				ConversationEditorToolBar^ get();
			}
		private:
			static ConversationEditorToolBar^ mInstance;
		};
	}
}