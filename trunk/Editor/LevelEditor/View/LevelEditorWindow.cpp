#include "Stdafx.h"
#include "LevelEditorWindow.h"
#include "../IsilmeControl.h"
#include "../Commands/NativeCommand.h"
#include "../Editor/AddEntityCommand.h"
#include "../Commands/AddEntity.h"
#include "../Proxy/EntityProxy.h"
#include "../Proxy/LayerProxy.h"
#include "../Proxy/LevelProxy.h"
#include "ObjectManager.h"
#include "../Commands/AddLayer.h"
#include "EntityPaletteTool.h"
#include "../Proxy/EntityPaletteProxy.h"
#include "../Proxy/FolderProxy.h"
#include "../Tool/ScrollerTool.h"
#include "../Tool/Tool.h"
#include "../Tool/SelectorTool.h"
#include "Engine/Core/Serialisation/StaticLevelSerialiser.h"
#include "../LevelEditorCommands.h"
#include "../Commands/RemoveEntity.h"

namespace LevelEditor
{
	namespace View
	{
		LevelEditorWindow^ LevelEditorWindow::Instance::get()
		{
			return mInstance;
		}

		LevelEditorWindow::LevelEditorWindow()
		{
			mLoadedLevels = gcnew Dictionary<String^, LevelProxy^>();
			mOldMouseX = -1;
			mOldMouseY = -1;
			mNeedToLoad = false;
			mInstance = this;
			
			mBorder = gcnew System::Windows::Controls::Border();
			this->AddChild(mBorder);
			host = gcnew LevelEditor::IsilmeHost();
			mBorder->Child = host;
			mHandle = host->Handle;
			host->UpdateFrame += gcnew UpdateFrameHandler(this, &LevelEditorWindow::OnFrameUpdate);

			host->MessageHook += gcnew System::Windows::Interop::HwndSourceHook(this, &LevelEditorWindow::ControlMsgFilter);

			this->MouseLeftButtonDown += gcnew MouseButtonEventHandler(this, &LevelEditorWindow::OnMouseDown);
			this->MouseLeftButtonUp += gcnew MouseButtonEventHandler(this, &LevelEditorWindow::OnMouseUp);

			// Создаем инструменты
			mEntityBrush = gcnew EntityBrush(CommandManager);
			mObjectsSelector = gcnew SelectorTool(CommandManager);

			mScrollTool = gcnew ScrollerTool();
			
			mEntityBrush->EntityType = "Cars/Car1";

			//mCurrentBrush = mEntityBrush;

			// Привязываем комманды
			CommandBindings->Add(
				gcnew CommandBinding(SelectEntityBrush, 
				gcnew ExecutedRoutedEventHandler(this, &LevelEditorWindow::ExecutedSelectEntityBrush), 
				gcnew CanExecuteRoutedEventHandler(this, &LevelEditorWindow::CanExecuteSelectEntityBrush)));

			SelectEntityBrush->CanExecuteTargets += gcnew Func<bool>(this, &LevelEditorWindow::CanExecuteSelectEntityBrush);
			SelectEntityBrush->ExecuteTargets += gcnew System::Action<Object^>(this, &LevelEditorWindow::ExecutedSelectEntityBrush);

			LevelEditorCommands::SelectObjectsSelector->CanExecuteTargets += gcnew Func<bool>(this, &LevelEditorWindow::CanExecuteSelectObjectsSelector);
			LevelEditorCommands::SelectObjectsSelector->ExecuteTargets += gcnew System::Action<Object^>(this, &LevelEditorWindow::ExecutedSelectObjectsSelector);

			LevelEditorCommands::DrawPhisics->CanExecuteTargets += gcnew Func<bool>(this, &LevelEditorWindow::CanExecuteDrawPhisics);
			LevelEditorCommands::DrawPhisics->ExecuteTargets += gcnew System::Action<Object^>(this, &LevelEditorWindow::ExecutedDrawPhisics);

			LevelEditorCommands::ActivatePhisics->CanExecuteTargets += gcnew Func<bool>(this, &LevelEditorWindow::CanExecuteActivatePhisics);
			LevelEditorCommands::ActivatePhisics->ExecuteTargets += gcnew System::Action<Object^>(this, &LevelEditorWindow::ExecutedActivatePhisics);

			CommandBindings->Add(
				gcnew CommandBinding(AddLayerCommand, 
				gcnew ExecutedRoutedEventHandler(this, &LevelEditorWindow::ExecutedAddLayer), 
				gcnew CanExecuteRoutedEventHandler(this, &LevelEditorWindow::CanExecuteAddLayer)));

			CommandBindings->Add(
				gcnew CommandBinding(SelectPaletteItem, 
				gcnew ExecutedRoutedEventHandler(this, &LevelEditorWindow::ExecutedSelectPaletteItem), 
				gcnew CanExecuteRoutedEventHandler(this, &LevelEditorWindow::CanExecuteSelectPaletteItem)));

			CommandBindings->Add(
				gcnew CommandBinding(System::Windows::Input::ApplicationCommands::Delete, 
				gcnew ExecutedRoutedEventHandler(this, &LevelEditorWindow::ExecutedRemoveEntity), 
				gcnew CanExecuteRoutedEventHandler(this, &LevelEditorWindow::CanExecuteRemoveEntity)));

			CommandBindings->Add(
				gcnew CommandBinding(System::Windows::Input::ApplicationCommands::Copy, 
				gcnew ExecutedRoutedEventHandler(this, &LevelEditorWindow::ExecutedCopyEntity), 
				gcnew CanExecuteRoutedEventHandler(this, &LevelEditorWindow::CanExecuteCopyEntity)));

			CommandBindings->Add(
				gcnew CommandBinding(System::Windows::Input::ApplicationCommands::Paste, 
				gcnew ExecutedRoutedEventHandler(this, &LevelEditorWindow::ExecutedPasteEntity), 
				gcnew CanExecuteRoutedEventHandler(this, &LevelEditorWindow::CanExecutePasteEntity)));
		}

		void LevelEditorWindow::OnMouseDown( Object^ sender, MouseButtonEventArgs^ e )
		{
			Focus();
			//mEntityBrush->Layer = gcnew LayerProxy(FactoryManager::GetSingleton()->GetLevel("Level2")->GetLayer("Trees"));
		}

		void LevelEditorWindow::OnMouseUp( Object^ sender, MouseButtonEventArgs^ e )
		{
			//LayerPtr layer = FactoryManager::GetSingleton()->GetLevel("Level2")->GetLayer("Trees");
			//EntityPtr entity = FactoryManager::GetSingleton()->CreateEntity("Cars/Car1", "");

			//Point^ point = e->GetPosition(this);

			//entity->SetPosition(point->X / 64, point->Y / 64);

			//Commands::NativeCommand^ command = gcnew Commands::NativeCommand(new editor::AddEntityCommand(layer, entity));
			//CommandManager->Execute(command);
		}

		System::IntPtr LevelEditorWindow:: ControlMsgFilter(IntPtr hwnd, int msg, IntPtr wParam, IntPtr lParam, bool% handled)
		{
			INT nWidth, nHeight;
			if (msg == WM_COMMAND)
			{
			
			}
			switch (msg) 
			{
			case WM_SIZE:
				nWidth = LOWORD(lParam.ToPointer());
				nHeight = HIWORD(lParam.ToPointer());
				host->Resize(nWidth, nHeight);
				break;
			case WM_MOUSEMOVE:
				//wmMouseMove(hwnd, wp, lp); // wp & lp store the co-ordinates here
				break;
			case WM_LBUTTONDOWN:
				//wmLButtonDown(hwnd, wp, lp);
				break;
			case WM_LBUTTONUP:
				//wmLButtonUp(hwnd, wp, lp);
				break;
			case WM_DESTROY:
				PostQuitMessage(0);       // Send WM_QUIT
				break;
			case WM_KEYDOWN:
//				wmKeyDown(hwnd, wp, lp);
				break;
			}
			//HGEGame::FrameFunction();
			SendMessage((HWND)mHandle->ToPointer(), msg, wParam.ToInt64(), lParam.ToInt64());
			return IntPtr::Zero;
		}

		void LevelEditorWindow::OnFrameUpdate( float elapsedTime )
		{
			static int oldHeight, oldWidth;
			if ((int)mBorder->ActualHeight != oldHeight && mBorder->ActualWidth != oldWidth)
				host->Resize(mBorder->ActualWidth, mBorder->ActualHeight);
			oldHeight = mBorder->ActualHeight;
			oldWidth = mBorder->ActualWidth;

			InputSystem* inputSystem = Engine::GetSingleton()->GetInputSystem();
			Vector2 mousePosition = Engine::GetSingleton()->GetInputSystem()->GetMousePosition();

			MouseData^ mouse = gcnew MouseData();
			mouse->x = mousePosition.x;
			mouse->y = mousePosition.y;

			// Нажатие мыши
			if (inputSystem->IsKeyDown(HGEK_LBUTTON))
			{
				mouse->button = MouseKey::LeftButton;
				if (mCurrentBrush != nullptr)
					mCurrentBrush->OnMouseDown(mouse);
				mScrollTool->OnMouseDown(mouse);
			}
			if (inputSystem->IsKeyDown(HGEK_MBUTTON))
			{
				mouse->button = MouseKey::MiddleButton;
				if (mCurrentBrush != nullptr)
					mCurrentBrush->OnMouseDown(mouse);
				mScrollTool->OnMouseDown(mouse);
			}
			if (inputSystem->IsKeyDown(HGEK_RBUTTON))
			{
				mouse->button = MouseKey::RightButton;
				if (mCurrentBrush != nullptr)
					mCurrentBrush->OnMouseDown(mouse);
				mScrollTool->OnMouseDown(mouse);
			}
			// Отпускание мыши
			if (inputSystem->IsKeyUp(HGEK_LBUTTON))
			{
				mouse->button = MouseKey::LeftButton;
				if (mCurrentBrush != nullptr)
					mCurrentBrush->OnMouseUp(mouse);
				mScrollTool->OnMouseUp(mouse);
			}
			if (inputSystem->IsKeyUp(HGEK_MBUTTON))
			{
				mouse->button = MouseKey::MiddleButton;
				if (mCurrentBrush != nullptr)
					mCurrentBrush->OnMouseUp(mouse);
				mScrollTool->OnMouseUp(mouse);
			}
			if (inputSystem->IsKeyUp(HGEK_RBUTTON))
			{
				mouse->button = MouseKey::RightButton;
				if (mCurrentBrush != nullptr)
					mCurrentBrush->OnMouseUp(mouse);
				mScrollTool->OnMouseUp(mouse);
			}

			// Перемещение мыши
			if (mouse->x != mOldMouseX || mouse->y != mOldMouseY)
			{
				if (mCurrentBrush != nullptr)
					mCurrentBrush->OnMouseMove(mouse);
				mScrollTool->OnMouseMove(mouse);
			}

			mOldMouseX = mouse->x;
			mOldMouseY = mouse->y;
		}

		void LevelEditorWindow::ExecutedSelectEntityBrush( Object^ sender, ExecutedRoutedEventArgs^ e )
		{
			if (Layer == nullptr)
			{
				Layer = Level->Layers[0];
			}

			mEntityBrush->Layer = Layer;
			mCurrentBrush = mEntityBrush;
		}

		void LevelEditorWindow::ExecutedSelectEntityBrush( Object^ param )
		{
			if (Layer == nullptr)
			{
				Layer = Level->Layers[0];
			}

			mEntityBrush->Layer = Layer;
			mCurrentBrush = mEntityBrush;
		}

		void LevelEditorWindow::CanExecuteSelectEntityBrush( Object^ sender, CanExecuteRoutedEventArgs^ e )
		{
			 e->CanExecute = true;
		}

		bool LevelEditorWindow::CanExecuteSelectEntityBrush()
		{
			return true;
		}

		void LevelEditorWindow::ExecutedAddLayer( Object^ sender, ExecutedRoutedEventArgs^ e )
		{
			LayerProxy^ layer = gcnew LayerProxy(LayerPtr(new ::Layer()));
			Commands::AddLayer^ command = gcnew Commands::AddLayer(mLevel, layer);
			CommandManager->Execute(command);
		}

		void LevelEditorWindow::CanExecuteAddLayer( System::Object^ sender, System::Windows::Input::CanExecuteRoutedEventArgs^ e )
		{
			e->CanExecute = true;
		}

		void LevelEditorWindow::CanExecuteSelectPaletteItem( System::Object^ sender, System::Windows::Input::CanExecuteRoutedEventArgs^ e )
		{
			e->CanExecute = true;
		}

		void LevelEditorWindow::ExecutedSelectPaletteItem( Object^ sender, ExecutedRoutedEventArgs^ e )
		{
			LevelEditor::Proxy::PaletteItemProxy^ paletteItem = dynamic_cast<PaletteItemProxy^>(e->Parameter);
			mEntityBrush->EntityType = paletteItem->FullName;
		}

		void LevelEditorWindow::Load()
		{

			if (!mNeedToLoad)
			{
				mNeedToLoad = true;
				return;
			}

			//if (mLoadedLevels->ContainsKey(FileName))
			//{
			//	mLevel = mLoadedLevels[FileName];
			//	//mEntityBrush->Layer = mLevel->Layers[0];

			//	mScrollTool->Level = Level;
			//	ObjectManager::Instance->Editor = this;
			//	HGEGame::GetSingleton()->GetStateManager()->GetState()->SetLevel(Level->mLevel->Value);
			//}
			//else
			//{
				CommandManager->Clear();
				LevelPtr level = FactoryManager::GetSingleton()->LoadLevel(static_cast<char*>(Marshal::StringToHGlobalAnsi(FileName).ToPointer()));
				//LevelPtr level = FactoryManager::GetSingleton()->GetLevel("Level2");//new Level());
				mLevel = gcnew property LevelProxy(level);
				//CameraPtr camera(new Camera());
				//camera->x = 0.0f;
				//camera->y = 0.0f;
				////level->Load("../Data/TestL.xml");
				//level->SetActiveCamera(camera);
				HGEGame::GetSingleton()->GetStateManager()->GetState()->SetLevel(level);

				ObjectManager::Instance->Editor = this;
				
				mEntityBrush->Layer = mLevel->Layers[0];

				mScrollTool->Level = Level;

				//// Тестируем создаение слоя
				//lua_State* state = Engine::GetSingleton()->GetLua()->GetState();
				//luaL_dostring(state, "testLayer = Layer(); testLayer:SetName(\"LuaLayer\"); Factory:GetLevel(\"Level2\"):AddLayer(testLayer); ");
				//// end
				Show();
			//	mLoadedLevels[FileName] = Level;
			//}
		}

		void LevelEditorWindow::ExecutedRemoveEntity( Object^ sender, ExecutedRoutedEventArgs^ e )
		{
			EntityProxy^ entity = dynamic_cast<EntityProxy^>(SelectedObject);
			if (entity != nullptr)
			{
				LayerProxy^ layer = entity->Layer;
				SelectedObject = nullptr;
				CommandManager->Execute(gcnew Commands::RemoveEntity(layer, entity));
			}
		}

		void LevelEditorWindow::CanExecuteRemoveEntity( System::Object^ sender, System::Windows::Input::CanExecuteRoutedEventArgs^ e )
		{
			e->CanExecute = (dynamic_cast<EntityProxy^>(SelectedObject) != nullptr);
		}

		void LevelEditorWindow::Save()
		{
			serialisation::StaticLevelSerialiser* serialiser = new serialisation::StaticLevelSerialiser();
			serialiser->Serialise(Level->mLevel->Value, (char*)(Marshal::StringToHGlobalAnsi(FileName).ToPointer()));
		}

		void LevelEditorWindow::ExecutedSelectObjectsSelector( Object^ param )
		{
			if (Layer == nullptr)
			{
				Layer = Level->Layers[0];
			}

			mObjectsSelector->Layer = Layer;
			mCurrentBrush = mObjectsSelector;
		}

		bool LevelEditorWindow::CanExecuteSelectObjectsSelector()
		{
			return true;
		}

		void LevelEditorWindow::OnClosing( System::ComponentModel::CancelEventArgs^ e )
		{
			e->Cancel = true;
			Hide();
		}

		void LevelEditorWindow::CanExecuteCopyEntity( System::Object^ sender, System::Windows::Input::CanExecuteRoutedEventArgs^ e )
		{
			e->CanExecute = dynamic_cast<EntityProxy^>(SelectedObject) != nullptr;
		}

		void LevelEditorWindow::ExecutedCopyEntity( Object^ sender, ExecutedRoutedEventArgs^ e )
		{
			EntityProxy^ entity = dynamic_cast<EntityProxy^>(SelectedObject);
			EntityCopyData^ data = entity->MakeCopy();

			System::Windows::Clipboard::SetData("EntityData", data);
		}

		void LevelEditorWindow::ExecutedPasteEntity( Object^ sender, ExecutedRoutedEventArgs^ e )
		{
			Object^ objData = System::Windows::Clipboard::GetData("EntityData");
		}

		void LevelEditorWindow::CanExecutePasteEntity( System::Object^ sender, System::Windows::Input::CanExecuteRoutedEventArgs^ e )
		{
			e->CanExecute = System::Windows::Clipboard::ContainsData("EntityData");
		}

		void LevelEditorWindow::ExecutedActivatePhisics( Object^ param )
		{
			Game::GetSingleton()->SetUsePhisics(!Game::GetSingleton()->GetUsePhisics());
		}

		bool LevelEditorWindow::CanExecuteActivatePhisics()
		{
			return true;
		}

		void LevelEditorWindow::ExecutedDrawPhisics( Object^ param )
		{
			Game::GetSingleton()->GetStateManager()->GetRenderer()->SetDrawPhisics(!Game::GetSingleton()->GetStateManager()->GetRenderer()->GetDrawPhisics());
		}

		bool LevelEditorWindow::CanExecuteDrawPhisics()
		{
			return true;
		}

		LevelProxy^ LevelEditorWindow::Level::get()
		{
			return mLevel;
		}

		LayerProxy^ LevelEditorWindow::Layer::get()
		{
			return mLayer;
		}

		void LevelEditorWindow::Layer::set(LayerProxy^ value)
		{
			mLayer = value;
			if (mCurrentBrush != nullptr)
			{
				((LayerTool^)mCurrentBrush)->Layer = mLayer;
			}
		}
	}
}