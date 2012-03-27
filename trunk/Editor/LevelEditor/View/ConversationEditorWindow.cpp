#include "Stdafx.h"
#include "ConversationEditorWindow.h"
#include "../Proxy/ConversationProxy.h"

using namespace System::Windows::Controls;
using namespace System;
using namespace System::Windows;
using namespace System::Windows::Data;
using namespace System::Collections::Generic;
using namespace System::Collections::ObjectModel;
using namespace LevelEditor::Proxy;
using namespace Common;

namespace LevelEditor
{
	namespace View
	{
		public ref class ConversationDataTemplateSelector : public DataTemplateSelector
		{
		public:
			static HierarchicalDataTemplate^ phraseTemplate;
			static HierarchicalDataTemplate^ refTemplate;

			ConversationDataTemplateSelector()
			{

			}
			virtual DataTemplate^ SelectTemplate(Object^ item, DependencyObject^ container) override
			{
				return phraseTemplate;
			}
		};

		ConversationEditorWindow::ConversationEditorWindow()
		{
			// Create dialog tree
			mDialogTree = gcnew System::Windows::Controls::TreeView();

			AddChild(mDialogTree);
		}

		void ConversationEditorWindow::Load( IEditableData^ data )
		{
			mConversation = dynamic_cast<ConversationProxy^>(data->Data);
			FileName = data->FileName;

			// Phrase template
			HierarchicalDataTemplate^ phraseTemplate = gcnew HierarchicalDataTemplate(PhraseProxy::typeid);
			FrameworkElementFactory^ praseEF = gcnew FrameworkElementFactory(Views::EditableTextBlock::typeid);
			Binding^ textBinding = gcnew Binding("Text");
			textBinding->Mode = BindingMode::TwoWay;
			praseEF->SetBinding(Views::EditableTextBlock::TextProperty, textBinding);
			phraseTemplate->VisualTree = praseEF;
			phraseTemplate->ItemsSource = gcnew Binding("Answers");
			phraseTemplate->ItemTemplate = phraseTemplate;

			// Conversation template
			HierarchicalDataTemplate^ convTemplate = gcnew HierarchicalDataTemplate(ConversationProxy::typeid);
			FrameworkElementFactory^ convEF = gcnew FrameworkElementFactory(TextBlock::typeid);
			convEF->SetBinding(TextBlock::TextProperty, gcnew System::Windows::Data::Binding("ID"));
			convTemplate->VisualTree = convEF;
			convTemplate->ItemsSource = gcnew System::Windows::Data::Binding("Phrases");
			convTemplate->ItemTemplate = phraseTemplate;
			
			// Binding
			List<ConversationProxy^>^ lst = gcnew List<ConversationProxy^>();
			lst->Add(mConversation);
			ObservableCollection<ConversationProxy^>^ collection = gcnew ObservableCollection<ConversationProxy^>(lst);
			
			// DataContext
			mDialogTree->DataContext = collection;
			mDialogTree->ItemTemplate = convTemplate;
			mDialogTree->SetBinding(TreeView::ItemsSourceProperty, gcnew Binding());
		}

	}
}