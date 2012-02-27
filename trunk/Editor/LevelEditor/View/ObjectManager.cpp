#include "Stdafx.h"
#include "ObjectManager.h"
#include "LevelEditorWindow.h"
#include "../Proxy/LevelProxy.h"
#include "../Proxy/LayerProxy.h"
#include "../Proxy/EntityProxy.h"
#include "../Commands/RemoveEntity.h"
#include "../Commands/RemoveLayer.h"
#include "../ResourceHelper.h"

using namespace LevelEditor::Commands;
using namespace System;
using namespace System::Windows;
using namespace System::Windows::Data;


namespace LevelEditor
{
	namespace View
	{
		ObjectManager::ObjectManager()
		{
			System::Windows::Controls::Grid^ mStackPanel = gcnew System::Windows::Controls::Grid();
			System::Windows::Controls::ToolBarTray^ tray = gcnew System::Windows::Controls::ToolBarTray();
			System::Windows::Controls::ToolBar^ mToolBar = gcnew System::Windows::Controls::ToolBar();
			System::Windows::Controls::Button^ mLayerUpBtn = gcnew System::Windows::Controls::Button();
			System::Windows::Controls::Button^ mLayerDownBtn = gcnew System::Windows::Controls::Button();
			System::Windows::Controls::Button^ mNewLayerBtn = gcnew System::Windows::Controls::Button();
			System::Windows::Controls::Button^ mTopBtn = gcnew System::Windows::Controls::Button();
			System::Windows::Controls::Button^ mBottomBtn = gcnew System::Windows::Controls::Button();
			System::Windows::Controls::Image^ image;

			// ToolbarTray
			tray->IsLocked = true;
			tray->ToolBars->Add(mToolBar);

			mObjectsTree = gcnew TreeView();

			// New
			image = gcnew System::Windows::Controls::Image();
			image->Source = ResourceHelper::GetPngSource("AddLayer.png");
			mNewLayerBtn->Content = image;
			mNewLayerBtn->ToolTip = "Add layer";

			// Up
			image = gcnew System::Windows::Controls::Image();
			image->Source = ResourceHelper::GetPngSource("Up.png");
			mLayerUpBtn->Content = image;
			mLayerUpBtn->ToolTip = "Move up";

			// Down
			image = gcnew System::Windows::Controls::Image();
			image->Source = ResourceHelper::GetPngSource("Down.png");
			mLayerDownBtn->Content = image;
			mLayerDownBtn->ToolTip = "Move down";

			// Top
			image = gcnew System::Windows::Controls::Image();
			image->Source = ResourceHelper::GetPngSource("Top.png");
			mTopBtn->Content = image;
			mTopBtn->ToolTip = "Move to the top";

			// Down
			image = gcnew System::Windows::Controls::Image();
			image->Source = ResourceHelper::GetPngSource("Bottom.png");
			mBottomBtn->Content = image;
			mBottomBtn->ToolTip = "Move to the bottom";

			//mToolBar->SetOverflowMode(System::Windows::Controls::OverflowMode::Never);
			mToolBar->Items->Add(mNewLayerBtn);
			mToolBar->Items->Add(gcnew System::Windows::Controls::Separator());
			mToolBar->Items->Add(mLayerUpBtn);
			mToolBar->Items->Add(mLayerDownBtn);
			mToolBar->Items->Add(mTopBtn);
			mToolBar->Items->Add(mBottomBtn);

			mStackPanel->Children->Add(tray);
			mStackPanel->Children->Add(mObjectsTree);
			mObjectsTree->Margin = System::Windows::Thickness(0, 36, 0, 0);

			AddChild(mStackPanel);

			CommandBindings->Add(
				gcnew CommandBinding(System::Windows::Input::ApplicationCommands::Delete, 
				gcnew ExecutedRoutedEventHandler(this, &ObjectManager::ExecutedRemove), 
				gcnew CanExecuteRoutedEventHandler(this, &ObjectManager::CanExecuteRemove)));

			mObjectsTree->MouseUp += gcnew MouseButtonEventHandler(this, &ObjectManager::OnObjectSelected);

			Title = "Objects";
			Icon = ResourceHelper::GetPngSource("Layers.png");
		}

		void ObjectManager::OnObjectSelected(Object^ sender, MouseButtonEventArgs^ e)
		{
			if (Editor != nullptr)
				Editor->SelectedObject = (IProxyObject^)(mObjectsTree->SelectedItem);
			if (dynamic_cast<LayerProxy^>(mObjectsTree->SelectedItem) != nullptr )
			{
				LayerProxy^ layer = dynamic_cast<LayerProxy^>(mObjectsTree->SelectedItem);
				LevelEditorWindow::Instance->Layer = layer;
			}
		}

		void ObjectManager::ExecutedRemove( Object^ sender, ExecutedRoutedEventArgs^ e )
		{
			if (dynamic_cast<EntityProxy^>(mObjectsTree->SelectedItem) != nullptr )
			{
				EntityProxy^ entity = dynamic_cast<EntityProxy^>(mObjectsTree->SelectedItem);
				LayerProxy^ layer = entity->Layer;

				Editor->CommandManager->Execute( gcnew RemoveEntity(layer, entity));
			}
			else if (dynamic_cast<LayerProxy^>(mObjectsTree->SelectedItem) != nullptr )
			{
				LayerProxy^ layer = dynamic_cast<LayerProxy^>(mObjectsTree->SelectedItem);
				LevelProxy^ level = layer->Level;

				Editor->CommandManager->Execute(gcnew RemoveLayer(level, layer));
			}
		}

		void ObjectManager::CanExecuteRemove( Object^ sender, CanExecuteRoutedEventArgs^ e )
		{
			e->CanExecute = mObjectsTree->SelectedItem != nullptr;
		}

		LevelEditorWindow^ ObjectManager::Editor::get()
		{
			return mEditor;
		}

		void ObjectManager::Editor::set(LevelEditorWindow^ editor)
		{
			mEditor = editor;

			// Привязываем данные
			//binding->Source = mObjectsTree->DataContext;

			System::Collections::ObjectModel::ObservableCollection<LevelProxy^>^ levelCollection = gcnew System::Collections::ObjectModel::ObservableCollection<LevelProxy^>();
			levelCollection->Add(editor->Level);
			mObjectsTree->SetBinding(System::Windows::Controls::TreeView::ItemsSourceProperty, gcnew Binding());
			mObjectsTree->DataContext = levelCollection;//->Layers[0];


			// Шаблон для слоя
			System::Windows::HierarchicalDataTemplate^ layerTemplate = gcnew HierarchicalDataTemplate(LayerProxy::typeid);
			FrameworkElementFactory^ layerElementFactory = gcnew FrameworkElementFactory(TextBlock::typeid);
			layerElementFactory->SetBinding(TextBlock::TextProperty, gcnew System::Windows::Data::Binding("Name"));
			layerTemplate->VisualTree = layerElementFactory;
			layerTemplate->ItemsSource = gcnew System::Windows::Data::Binding("Entities");
			
			// Шаблон для сущности
			System::Windows::HierarchicalDataTemplate^ entityTemplate = gcnew HierarchicalDataTemplate(EntityProxy::typeid);
			FrameworkElementFactory^ entityElementFactory = gcnew FrameworkElementFactory(TextBlock::typeid);
			entityElementFactory->SetBinding(TextBlock::TextProperty, gcnew System::Windows::Data::Binding("Name"));
			entityTemplate->VisualTree = entityElementFactory;
			layerTemplate->ItemTemplate = entityTemplate;

			// Шаблон для уровня
			HierarchicalDataTemplate^ levelTemplate = gcnew HierarchicalDataTemplate(LevelProxy::typeid);
			FrameworkElementFactory^ levelEF = gcnew FrameworkElementFactory(TextBlock::typeid);
			levelEF->SetBinding(TextBlock::TextProperty, gcnew Binding("ID"));
			levelTemplate->VisualTree = levelEF;
			levelTemplate->ItemTemplate = layerTemplate;
			levelTemplate->ItemsSource = gcnew Binding("Layers");

			// Устанавливаем шаблон
			mObjectsTree->ItemTemplate = levelTemplate;
		}

		ObjectManager^ ObjectManager::Instance::get()
		{
			if (mInstance == nullptr)
				mInstance = gcnew ObjectManager();
			
			return mInstance;
		}
	}
}