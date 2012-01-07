#include "Stdafx.h"
#include "ObjectManager.h"
#include "LevelEditorWindow.h"
#include "../Proxy/LevelProxy.h"
#include "../Proxy/LayerProxy.h"
#include "../Proxy/EntityProxy.h"
#include "../Commands/RemoveEntity.h"
#include "../Commands/RemoveLayer.h"

using namespace LevelEditor::Commands;

namespace LevelEditor
{
	namespace View
	{
		ObjectManager::ObjectManager()
		{
			System::Windows::Controls::Grid^ mStackPanel = gcnew System::Windows::Controls::Grid();
			System::Windows::Controls::ToolBar^ mToolBar = gcnew System::Windows::Controls::ToolBar();
			System::Windows::Controls::Button^ mLayerUpBtn = gcnew System::Windows::Controls::Button();
			System::Windows::Controls::Button^ mLayerDownBtn = gcnew System::Windows::Controls::Button();
			mObjectsTree = gcnew TreeView();

			// Слой вверх
			mLayerUpBtn->Content = "Up";

			// Слой вниз
			mLayerDownBtn->Content = "Down";

			mToolBar->Items->Add(mLayerUpBtn);
			mToolBar->Items->Add(mLayerDownBtn);

			mStackPanel->Children->Add(mToolBar);
			mStackPanel->Children->Add(mObjectsTree);
			mObjectsTree->Margin = System::Windows::Thickness(0, 36, 0, 0);

			AddChild(mStackPanel);

			CommandBindings->Add(
				gcnew CommandBinding(System::Windows::Input::ApplicationCommands::Delete, 
				gcnew ExecutedRoutedEventHandler(this, &ObjectManager::ExecutedRemove), 
				gcnew CanExecuteRoutedEventHandler(this, &ObjectManager::CanExecuteRemove)));

			mObjectsTree->MouseUp += gcnew MouseButtonEventHandler(this, &ObjectManager::OnObjectSelected);

			Title = "Objects";
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
			System::Windows::Data::Binding^ binding = gcnew System::Windows::Data::Binding("Layers");
			//binding->Source = mObjectsTree->DataContext;

			mObjectsTree->SetBinding(TreeView::ItemsSourceProperty, binding);
			mObjectsTree->DataContext = editor->Level;//->Layers[0];

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

			// Устанавливаем шаблон
			mObjectsTree->ItemTemplate = layerTemplate;
			//for each (LayerProxy^ layer in editor->Level->Layers)
			//{
			//	TreeViewItem^ item = gcnew TreeViewItem();
			//	item->Header = "test";
			//	mObjectsTree->Items->Add(item);
			//	
			//}
		}

		ObjectManager^ ObjectManager::Instance::get()
		{
			if (mInstance == nullptr)
				mInstance = gcnew ObjectManager();
			
			return mInstance;
		}
	}
}