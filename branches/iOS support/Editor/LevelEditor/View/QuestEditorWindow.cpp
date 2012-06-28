#include "Stdafx.h"
#include "QuestEditorWindow.h"
#include "../Proxy/StoryProxy.h"
#include "../Proxy/QuestProxy.h"
#include "../ResourceHelper.h"
#include "../Commands/AddQuest.h"
#include "../Commands/RemoveStage.h"
#include "../Commands/RemoveQuest.h"
#include "../Proxy/StageProxy.h"
#include "../Commands/AddStage.h"
#include "../Serialisation/StorySerialiser.h"

using namespace System::Windows::Controls;
using namespace System::Windows::Media;
using namespace System::Windows::Data;
using namespace System::Collections::Generic;
using namespace System::Collections::ObjectModel;
using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Windows::Input;
using namespace System::Windows;
using namespace LevelEditor::Proxy;
using namespace Common::Views;

namespace LevelEditor
{
	namespace View
	{
		QuestEditorWindow::QuestEditorWindow()
		{
			mStoryTree = gcnew TreeView();
			mStoryTree->SelectedItemChanged += gcnew RoutedPropertyChangedEventHandler<Object^>(this, &QuestEditorWindow::OnStoryTree_SelectedItemChanged);
			AddChild(mStoryTree);

			// Command bindings
			CommandBindings->Add(gcnew CommandBinding(
				AddQuest, 
				gcnew ExecutedRoutedEventHandler(this, &QuestEditorWindow::ExecutedAddQuest), 
				gcnew CanExecuteRoutedEventHandler(this, &QuestEditorWindow::CanExecuteAddQuest)));
			CommandBindings->Add(gcnew CommandBinding(
				AddStage, 
				gcnew ExecutedRoutedEventHandler(this, &QuestEditorWindow::ExecutedAddStage), 
				gcnew CanExecuteRoutedEventHandler(this, &QuestEditorWindow::CanExecuteAddStage)));
			CommandBindings->Add(gcnew CommandBinding(
				ApplicationCommands::Delete, 
				gcnew ExecutedRoutedEventHandler(this, &QuestEditorWindow::ExecutedDelete), 
				gcnew CanExecuteRoutedEventHandler(this, &QuestEditorWindow::CanExecuteDelete)));
			CommandBindings->Add(gcnew CommandBinding(
				ApplicationCommands::Copy, 
				gcnew ExecutedRoutedEventHandler(this, &QuestEditorWindow::ExecutedCopy), 
				gcnew CanExecuteRoutedEventHandler(this, &QuestEditorWindow::CanExecuteCopy)));
			CommandBindings->Add(gcnew CommandBinding(
				ApplicationCommands::Cut, 
				gcnew ExecutedRoutedEventHandler(this, &QuestEditorWindow::ExecutedCut), 
				gcnew CanExecuteRoutedEventHandler(this, &QuestEditorWindow::CanExecuteCut)));
			CommandBindings->Add(gcnew CommandBinding(
				ApplicationCommands::Paste, 
				gcnew ExecutedRoutedEventHandler(this, &QuestEditorWindow::ExecutedPaste), 
				gcnew CanExecuteRoutedEventHandler(this, &QuestEditorWindow::CanExecutePaste)));

			// Stage template
			HierarchicalDataTemplate^ stageTemplate = gcnew HierarchicalDataTemplate();
			FrameworkElementFactory^ stack = gcnew FrameworkElementFactory(StackPanel::typeid);
			stack->SetValue(StackPanel::OrientationProperty, Orientation::Horizontal);
			FrameworkElementFactory^ icon = gcnew FrameworkElementFactory(Image::typeid);
			icon->SetValue(Image::SourceProperty, ResourceHelper::GetPngSource("Stage.png"));
			stageTemplate->VisualTree = stack;
			FrameworkElementFactory^ text = gcnew FrameworkElementFactory(EditableTextBlock::typeid);
			Binding^ binding = gcnew Binding("Text");
			binding->Mode = BindingMode::TwoWay;
			text->SetValue(EditableTextBlock::TextProperty, binding);

			stack->AppendChild(icon);
			stack->AppendChild(text);
			// Quest template
			HierarchicalDataTemplate^ questTemplate = gcnew HierarchicalDataTemplate();
			stack = gcnew FrameworkElementFactory(StackPanel::typeid);
			stack->SetValue(StackPanel::OrientationProperty, Orientation::Horizontal);
			icon = gcnew FrameworkElementFactory(Image::typeid);
			icon->SetValue(Image::SourceProperty, ResourceHelper::GetPngSource("Quest.png"));
			questTemplate->VisualTree = stack;
			questTemplate->ItemsSource = gcnew Binding("Stages");
			text = gcnew FrameworkElementFactory(EditableTextBlock::typeid);
			binding = gcnew Binding("Title");
			binding->Mode = BindingMode::TwoWay;
			text->SetValue(EditableTextBlock::TextProperty, binding);
			questTemplate->ItemTemplate = stageTemplate;
			stack->AppendChild(icon);
			stack->AppendChild(text);

			// Story template
			HierarchicalDataTemplate^ storyTemplate = gcnew HierarchicalDataTemplate();
			stack = gcnew FrameworkElementFactory(StackPanel::typeid);
			stack->SetValue(StackPanel::OrientationProperty, Orientation::Horizontal);
			icon = gcnew FrameworkElementFactory(Image::typeid);
			icon->SetValue(Image::SourceProperty, ResourceHelper::GetPngSource("Quest.png"));
			text = gcnew FrameworkElementFactory(TextBlock::typeid);
			text->SetValue(TextBlock::TextProperty, "Story");
			stack->AppendChild(icon);
			stack->AppendChild(text);
			storyTemplate->VisualTree = stack;
			storyTemplate->ItemsSource = gcnew Binding("Quests");
			storyTemplate->ItemTemplate = questTemplate;
			mStoryTree->SetBinding(TreeView::ItemsSourceProperty, gcnew Binding());
			mStoryTree->ItemTemplate = storyTemplate;
		}

		void QuestEditorWindow::Load( Common::IEditableData^ data )
		{
			mStory = dynamic_cast<Proxy::StoryProxy^>(data->Data);
			if (mStory == nullptr)
				return;

			// Binding
			List<StoryProxy^>^ lst = gcnew List<StoryProxy^>();
			lst->Add(mStory);

			mStoryTree->DataContext = gcnew ObservableCollection<StoryProxy^>(lst);
		}

		void QuestEditorWindow::Load()
		{

		}

		void QuestEditorWindow::Save()
		{
			serialisation::XMLStorySerialiser serialiser;
			serialiser.Serialise(mStory->mStory->Value, (char*)Marshal::StringToHGlobalAnsi(FileName).ToPointer());
		}

		void QuestEditorWindow::ExecutedCopy( System::Object^ sender, System::Windows::Input::ExecutedRoutedEventArgs^ e )
		{
			QuestProxy^ quest = dynamic_cast<QuestProxy^>(mStoryTree->SelectedItem);
			if (quest != nullptr)
			{
				QuestCopyData^ data = quest->MakeCopy();
				System::Windows::Clipboard::SetData("QuestData", data);
			}
			else
			{
				StageProxy^ stage = dynamic_cast<StageProxy^>(mStoryTree->SelectedItem);
				StageCopyData^ data = stage->MakeCopy();
				System::Windows::Clipboard::SetData("QuestData", data);
			}
		}

		void QuestEditorWindow::CanExecuteCopy( System::Object^ sender, System::Windows::Input::CanExecuteRoutedEventArgs^ e )
		{
			e->CanExecute = mStoryTree->SelectedItem != nullptr && mStoryTree->SelectedItem != mStory;
		}

		void QuestEditorWindow::ExecutedCut( System::Object^ sender, System::Windows::Input::ExecutedRoutedEventArgs^ e )
		{
			QuestProxy^ quest = dynamic_cast<QuestProxy^>(mStoryTree->SelectedItem);
			if (quest != nullptr)
			{
				QuestCopyData^ data = quest->MakeCopy();
				System::Windows::Clipboard::SetData("QuestData", data);
				CommandManager->Execute(gcnew Commands::RemoveQuest(mStory, quest));
			}
			else
			{
				StageProxy^ stage = dynamic_cast<StageProxy^>(mStoryTree->SelectedItem);
				StageCopyData^ data = stage->MakeCopy();
				System::Windows::Clipboard::SetData("QuestData", data);
				CommandManager->Execute(gcnew Commands::RemoveStage(stage->Quest, stage));
			}
		}

		void QuestEditorWindow::CanExecuteCut( System::Object^ sender, System::Windows::Input::CanExecuteRoutedEventArgs^ e )
		{
			e->CanExecute = mStoryTree->SelectedItem != nullptr && mStoryTree->SelectedItem != mStory;
		}

		void QuestEditorWindow::ExecutedPaste( System::Object^ sender, System::Windows::Input::ExecutedRoutedEventArgs^ e )
		{
			Object^ obj = System::Windows::Clipboard::GetData("QuestData");
			StageCopyData^ sData = dynamic_cast<StageCopyData^>(obj);
			QuestCopyData^ qData = dynamic_cast<QuestCopyData^>(obj);
			if (sData != nullptr)
			{
				StageProxy^ stage = gcnew StageProxy(sData);
				StageProxy^ selected = dynamic_cast<StageProxy^>(mStoryTree->SelectedItem);
				stage->ID += 100;
				if (selected != nullptr)
				{
					stage->ID = selected->Quest->GenerateID();
					CommandManager->Execute(gcnew Commands::AddStage(selected->Quest, stage));
				}
				else
				{
					QuestProxy^ q = dynamic_cast<QuestProxy^>(mStoryTree->SelectedItem);
					stage->ID = q->GenerateID();
					CommandManager->Execute(gcnew Commands::AddStage(q, stage));
				}
			}
			else
			{
				QuestProxy^ q = gcnew QuestProxy(qData);
				q->ID += "_1";
				CommandManager->Execute(gcnew Commands::AddQuest(mStory, q));
			}
		}

		void QuestEditorWindow::CanExecutePaste( System::Object^ sender, System::Windows::Input::CanExecuteRoutedEventArgs^ e )
		{
			Object^ obj = System::Windows::Clipboard::GetData("QuestData");
			StageCopyData^ sData = dynamic_cast<StageCopyData^>(obj);
			QuestCopyData^ qData = dynamic_cast<QuestCopyData^>(obj);

			e->CanExecute = mStoryTree->SelectedItem != nullptr && 
				((qData != nullptr) || (sData != nullptr && mStoryTree->SelectedItem != mStory));
		}

		void QuestEditorWindow::ExecutedAddQuest( System::Object^ sender, System::Windows::Input::ExecutedRoutedEventArgs^ e )
		{
			QuestProxy^ q = gcnew QuestProxy();
			q->Title = "new quest";
			q->ID = mStory->GenerateID();
			CommandManager->Execute(gcnew Commands::AddQuest(mStory, q));
		}

		void QuestEditorWindow::CanExecuteAddQuest( System::Object^ sender, System::Windows::Input::CanExecuteRoutedEventArgs^ e )
		{
			e->CanExecute = true;
		}

		void QuestEditorWindow::ExecutedAddStage( System::Object^ sender, System::Windows::Input::ExecutedRoutedEventArgs^ e )
		{
			StageProxy^ stage = gcnew StageProxy();
			StageProxy^ selected = dynamic_cast<StageProxy^>(mStoryTree->SelectedItem);
			stage->Text = "Text...";
			if (selected != nullptr)
			{
				stage->ID = selected->Quest->GenerateID();
				CommandManager->Execute(gcnew Commands::AddStage(selected->Quest, stage));
			}
			else
			{
				QuestProxy^ q = dynamic_cast<QuestProxy^>(mStoryTree->SelectedItem);
				stage->ID = q->GenerateID();
				CommandManager->Execute(gcnew Commands::AddStage(q, stage));
			}
		}

		void QuestEditorWindow::CanExecuteAddStage( System::Object^ sender, System::Windows::Input::CanExecuteRoutedEventArgs^ e )
		{
			e->CanExecute = mStoryTree->SelectedItem != nullptr && mStoryTree->SelectedItem != mStory;
		}

		void QuestEditorWindow::ExecutedDelete( System::Object^ sender, System::Windows::Input::ExecutedRoutedEventArgs^ e )
		{
			StageProxy^ selected = dynamic_cast<StageProxy^>(mStoryTree->SelectedItem);
			if (selected != nullptr)
			{
				CommandManager->Execute(gcnew Commands::RemoveStage(selected->Quest, selected));
			}
			else
			{
				QuestProxy^ q = dynamic_cast<QuestProxy^>(mStoryTree->SelectedItem);
				CommandManager->Execute(gcnew Commands::RemoveQuest(mStory, q));
			}
		}

		void QuestEditorWindow::CanExecuteDelete( System::Object^ sender, System::Windows::Input::CanExecuteRoutedEventArgs^ e )
		{
			e->CanExecute = mStoryTree->SelectedItem != nullptr && mStoryTree->SelectedItem != mStory;
		}

		void QuestEditorWindow::OnStoryTree_SelectedItemChanged( System::Object^ sender, System::Windows::RoutedPropertyChangedEventArgs<Object^>^ e )
		{
			SelectedObject = dynamic_cast<Common::IProxyObject^>(mStoryTree->SelectedItem);
		}

		QuestEditorToolBar::QuestEditorToolBar()
		{
			// Add quest
			Button^ mAddQuest = gcnew Button();
			mAddQuest->Command = QuestEditorWindow::AddQuest;
			Image^ image = gcnew System::Windows::Controls::Image();
			image->Source = ResourceHelper::GetPngSource("AddQuest.png");
			mAddQuest->Content = image;
			mAddQuest->ToolTip = "Add new quest";

			// Add stage
			Button^ mAddStage = gcnew Button();
			mAddStage->Command = QuestEditorWindow::AddStage;
			image = gcnew System::Windows::Controls::Image();
			image->Source = ResourceHelper::GetPngSource("AddStage.png");
			mAddStage->Content = image;
			mAddStage->ToolTip = "Add new stage";

			AddChild(mAddQuest);
			AddChild(mAddStage);
		}

		QuestEditorToolBar^ QuestEditorToolBar::Instance::get()
		{
			if (mInstance == nullptr)
			{
				mInstance = gcnew QuestEditorToolBar();
			}

			return mInstance;
		}


	}
}