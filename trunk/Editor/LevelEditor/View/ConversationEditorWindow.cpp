#include "Stdafx.h"
#include "ConversationEditorWindow.h"
#include "../Proxy/ConversationProxy.h"
#include "../Proxy/PhraseProxy.h"
#include "../Commands/AddPhrase.h"
#include "../Commands/RemovePhrase.h"
#include "../ResourceHelper.h"

using namespace System::Windows::Controls;
using namespace System;
using namespace System::Windows;
using namespace System::Windows::Input;
using namespace System::Windows::Data;
using namespace System::Collections::Generic;
using namespace System::Collections::ObjectModel;
using namespace LevelEditor::Proxy;
using namespace LevelEditor::Commands;
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
			// Command bindings
			CommandBindings->Add(gcnew CommandBinding(
				AddPhraseCommand, 
				gcnew ExecutedRoutedEventHandler(this, &ConversationEditorWindow::ExecutedAddPhrase), 
				gcnew CanExecuteRoutedEventHandler(this, &ConversationEditorWindow::CanExecuteAddPhrase)));
			CommandBindings->Add(gcnew CommandBinding(
				PasteRefCommand, 
				gcnew ExecutedRoutedEventHandler(this, &ConversationEditorWindow::ExecutedPasteRef), 
				gcnew CanExecuteRoutedEventHandler(this, &ConversationEditorWindow::CanExecutePasteRef)));
			CommandBindings->Add(gcnew CommandBinding(
				ApplicationCommands::Delete, 
				gcnew ExecutedRoutedEventHandler(this, &ConversationEditorWindow::ExecutedDelete), 
				gcnew CanExecuteRoutedEventHandler(this, &ConversationEditorWindow::CanExecuteDelete)));
			CommandBindings->Add(gcnew CommandBinding(
				ApplicationCommands::Copy, 
				gcnew ExecutedRoutedEventHandler(this, &ConversationEditorWindow::ExecutedCopy), 
				gcnew CanExecuteRoutedEventHandler(this, &ConversationEditorWindow::CanExecuteCopy)));
			CommandBindings->Add(gcnew CommandBinding(
				ApplicationCommands::Cut, 
				gcnew ExecutedRoutedEventHandler(this, &ConversationEditorWindow::ExecutedCut), 
				gcnew CanExecuteRoutedEventHandler(this, &ConversationEditorWindow::CanExecuteCut)));
			CommandBindings->Add(gcnew CommandBinding(
				ApplicationCommands::Paste, 
				gcnew ExecutedRoutedEventHandler(this, &ConversationEditorWindow::ExecutedPaste), 
				gcnew CanExecuteRoutedEventHandler(this, &ConversationEditorWindow::CanExecutePaste)));

			// Create dialog tree
			mDialogTree = gcnew System::Windows::Controls::TreeView();

			// Event handlers
			mDialogTree->SelectedItemChanged += gcnew RoutedPropertyChangedEventHandler<Object^>(this, &ConversationEditorWindow::OnDialogTree_SelectedItemChanged);

			AddChild(mDialogTree);
		}

		void ConversationEditorWindow::Load( IEditableData^ data )
		{
			mConversation = dynamic_cast<ConversationProxy^>(data->Data);
			FileName = data->FileName;

			// PC speaker
			HierarchicalDataTemplate^ PCPhraseTemplate = gcnew HierarchicalDataTemplate(PhraseProxy::typeid);
			FrameworkElementFactory^ stack = gcnew FrameworkElementFactory(StackPanel::typeid);
			stack->SetValue(StackPanel::OrientationProperty, Orientation::Horizontal);
			FrameworkElementFactory^ iconEF = gcnew FrameworkElementFactory(System::Windows::Controls::Image::typeid);
			iconEF->SetValue(System::Windows::Controls::Image::SourceProperty, ResourceHelper::GetPngSource("PCSpeaker.png"));
			FrameworkElementFactory^ textEF = gcnew FrameworkElementFactory(Views::EditableTextBlock::typeid);
			Binding^ textBinding = gcnew Binding("Text");
			textBinding->Mode = BindingMode::TwoWay;
			textEF->SetBinding(Views::EditableTextBlock::TextProperty, textBinding);

			stack->AppendChild(iconEF);
			stack->AppendChild(textEF);
			PCPhraseTemplate->VisualTree = stack;
			PCPhraseTemplate->ItemsSource = gcnew Binding("Answers");

			// NPCPhraseTemplate
			HierarchicalDataTemplate^ NPCPhraseTemplate = gcnew HierarchicalDataTemplate(PhraseProxy::typeid);
			stack = gcnew FrameworkElementFactory(StackPanel::typeid);
			stack->SetValue(StackPanel::OrientationProperty, Orientation::Horizontal);
			iconEF = gcnew FrameworkElementFactory(System::Windows::Controls::Image::typeid);
			iconEF->SetValue(System::Windows::Controls::Image::SourceProperty, ResourceHelper::GetPngSource("NPCSpeaker.png"));
			textEF = gcnew FrameworkElementFactory(Views::EditableTextBlock::typeid);
			textBinding = gcnew Binding("Text");
			textBinding->Mode = BindingMode::TwoWay;
			textEF->SetBinding(Views::EditableTextBlock::TextProperty, textBinding);

			stack->AppendChild(iconEF);
			stack->AppendChild(textEF);
			NPCPhraseTemplate->VisualTree = stack;
			NPCPhraseTemplate->ItemsSource = gcnew Binding("Answers");

			PCPhraseTemplate->ItemTemplate = NPCPhraseTemplate;
			NPCPhraseTemplate->ItemTemplate = PCPhraseTemplate;

			// Conversation template
			HierarchicalDataTemplate^ convTemplate = gcnew HierarchicalDataTemplate(ConversationProxy::typeid);
			FrameworkElementFactory^ convEF = gcnew FrameworkElementFactory(TextBlock::typeid);
			convEF->SetBinding(TextBlock::TextProperty, gcnew System::Windows::Data::Binding("ID"));
			convTemplate->VisualTree = convEF;
			convTemplate->ItemsSource = gcnew System::Windows::Data::Binding("Phrases");
			convTemplate->ItemTemplate = NPCPhraseTemplate;
			
			// Binding
			List<ConversationProxy^>^ lst = gcnew List<ConversationProxy^>();
			lst->Add(mConversation);
			ObservableCollection<ConversationProxy^>^ collection = gcnew ObservableCollection<ConversationProxy^>(lst);
			
			// DataContext
			mDialogTree->DataContext = collection;
			mDialogTree->ItemTemplate = convTemplate;
			mDialogTree->SetBinding(TreeView::ItemsSourceProperty, gcnew Binding());
		}

		void ConversationEditorWindow::Save()
		{
			mConversation->SaveToFile(FileName);
		}

		void ConversationEditorWindow::ExecutedAddPhrase( System::Object^ sender, System::Windows::Input::ExecutedRoutedEventArgs^ e )
		{
			if (mDialogTree->SelectedItem == mConversation)
			{
				PhraseProxy^ phrase = gcnew PhraseProxy();
				phrase->Text = "Text...";
				CommandManager->Execute(gcnew AddPhrase(mConversation, phrase));
			}
			else
			{
				PhraseProxy^ selected = dynamic_cast<PhraseProxy^>(mDialogTree->SelectedItem);
				if (selected != nullptr)
				{
					PhraseProxy^ phrase = gcnew PhraseProxy();
					phrase->Text = "Text...";
					CommandManager->Execute(gcnew AddPhrase(selected, phrase));
				}
			}
		}

		void ConversationEditorWindow::CanExecuteAddPhrase( System::Object^ sender, System::Windows::Input::CanExecuteRoutedEventArgs^ e )
		{
			e->CanExecute = mDialogTree->SelectedItem != nullptr;
		}

		void ConversationEditorWindow::ExecutedPasteRef( System::Object^ sender, System::Windows::Input::ExecutedRoutedEventArgs^ e )
		{
			Object^ objData = System::Windows::Clipboard::GetData("PhraseData");
			
			PhraseCopyData^ pData = dynamic_cast<PhraseCopyData^>(objData);

			PhraseProxy^ original = mConversation->FindByInternalID(pData->InternalID);
			if (original == nullptr)
			{
				System::Windows::MessageBox::Show(nullptr, "Impossible insert reference to a phrase into this conversation", "Warning");
				return;
			}
			PhraseProxy^ phrase = gcnew PhraseProxy(original);

			if (mDialogTree->SelectedItem == mConversation)
			{
				CommandManager->Execute(gcnew AddPhrase(mConversation, phrase));
			}
			else
			{
				PhraseProxy^ selected = dynamic_cast<PhraseProxy^>(mDialogTree->SelectedItem);
				if (selected != nullptr)
				{
					CommandManager->Execute(gcnew AddPhrase(selected, phrase));
				}
			}
		}

		void ConversationEditorWindow::CanExecutePasteRef( System::Object^ sender, System::Windows::Input::CanExecuteRoutedEventArgs^ e )
		{
			e->CanExecute = System::Windows::Clipboard::ContainsData("PhraseData") && mDialogTree->SelectedItem != nullptr;;
		}

		void ConversationEditorWindow::ExecutedDelete( System::Object^ sender, System::Windows::Input::ExecutedRoutedEventArgs^ e )
		{
			PhraseProxy^ selected = dynamic_cast<PhraseProxy^>(mDialogTree->SelectedItem);
			CommandManager->Execute(gcnew RemovePhrase(selected));
		}

		void ConversationEditorWindow::CanExecuteDelete( System::Object^ sender, System::Windows::Input::CanExecuteRoutedEventArgs^ e )
		{
			PhraseProxy^ selected = dynamic_cast<PhraseProxy^>(mDialogTree->SelectedItem);
			e->CanExecute = selected != nullptr;
		}

		void ConversationEditorWindow::OnDialogTree_SelectedItemChanged( System::Object^ sender, System::Windows::RoutedPropertyChangedEventArgs<Object^>^ e )
		{
			SelectedObject = dynamic_cast<IProxyObject^>(mDialogTree->SelectedItem);
		}

		void ConversationEditorWindow::ExecutedCopy( System::Object^ sender, System::Windows::Input::ExecutedRoutedEventArgs^ e )
		{
			PhraseProxy^ selected = dynamic_cast<PhraseProxy^>(mDialogTree->SelectedItem);
			PhraseCopyData^ data = selected->MakeCopy();

			System::Windows::Clipboard::SetData("PhraseData", data);
		}

		void ConversationEditorWindow::CanExecuteCopy( System::Object^ sender, System::Windows::Input::CanExecuteRoutedEventArgs^ e )
		{
			PhraseProxy^ selected = dynamic_cast<PhraseProxy^>(mDialogTree->SelectedItem);
			e->CanExecute = selected != nullptr;
		}

		void ConversationEditorWindow::ExecutedCut( System::Object^ sender, System::Windows::Input::ExecutedRoutedEventArgs^ e )
		{
			PhraseProxy^ selected = dynamic_cast<PhraseProxy^>(mDialogTree->SelectedItem);
			PhraseCopyData^ data = selected->MakeCopy();

			System::Windows::Clipboard::SetData("PhraseData", data);

			CommandManager->Execute(gcnew RemovePhrase(selected));
		}

		void ConversationEditorWindow::CanExecuteCut( System::Object^ sender, System::Windows::Input::CanExecuteRoutedEventArgs^ e )
		{
			PhraseProxy^ selected = dynamic_cast<PhraseProxy^>(mDialogTree->SelectedItem);
			e->CanExecute = selected != nullptr;
		}

		void ConversationEditorWindow::ExecutedPaste( System::Object^ sender, System::Windows::Input::ExecutedRoutedEventArgs^ e )
		{
			Object^ objData = System::Windows::Clipboard::GetData("PhraseData");
			PhraseCopyData^ pData = dynamic_cast<PhraseCopyData^>(objData);
			PhraseProxy^ phrase = gcnew PhraseProxy(pData);
			if (mDialogTree->SelectedItem == mConversation)
			{
				CommandManager->Execute(gcnew AddPhrase(mConversation, phrase));
			}
			else
			{
				PhraseProxy^ selected = dynamic_cast<PhraseProxy^>(mDialogTree->SelectedItem);
				if (selected != nullptr)
				{
					CommandManager->Execute(gcnew AddPhrase(selected, phrase));
				}
			}
		}

		void ConversationEditorWindow::CanExecutePaste( System::Object^ sender, System::Windows::Input::CanExecuteRoutedEventArgs^ e )
		{
			e->CanExecute = System::Windows::Clipboard::ContainsData("PhraseData") && mDialogTree->SelectedItem != nullptr;
		}


		ConversationEditorToolBar::ConversationEditorToolBar()
		{
			Button^ mAddPhrase = gcnew Button();
			mAddPhrase->Command = ConversationEditorWindow::AddPhraseCommand;
			Image^ image = gcnew System::Windows::Controls::Image();
			image->Source = ResourceHelper::GetPngSource("AddPhrase.png");
			mAddPhrase->Content = image;
			mAddPhrase->ToolTip = "Add new phrase";

			Button^ mPasteRef = gcnew Button();
			image = gcnew System::Windows::Controls::Image();
			image->Source = ResourceHelper::GetPngSource("PasteRef.png");
			mPasteRef->Content = image;
			mPasteRef->Command = ConversationEditorWindow::PasteRefCommand;
			mPasteRef->ToolTip = "Paste reference phrase";

			AddChild(mAddPhrase);
			AddChild(mPasteRef);
		}

		ConversationEditorToolBar^ ConversationEditorToolBar::Instance::get()
		{
			if (mInstance == nullptr)
				mInstance = gcnew ConversationEditorToolBar();
			return mInstance;
		}
	}
}