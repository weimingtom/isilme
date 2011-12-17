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

namespace LevelEditor
{
	namespace View
	{

		LevelEditorWindow::LevelEditorWindow()
		{
			System::Windows::Controls::Border^ mBorder;
			mBorder = gcnew System::Windows::Controls::Border();
			this->AddChild(mBorder);
			LevelEditor::IsilmeHost^ host = gcnew LevelEditor::IsilmeHost();
			mBorder->Child = host;
			mHandle = host->Handle;
			host->UpdateFrame += gcnew UpdateFrameHandler(this, &LevelEditorWindow::OnFrameUpdate);

			host->MessageHook += gcnew System::Windows::Interop::HwndSourceHook(this, &LevelEditorWindow::ControlMsgFilter);

			this->MouseLeftButtonDown += gcnew MouseButtonEventHandler(this, &LevelEditorWindow::OnMouseDown);
			this->MouseLeftButtonUp += gcnew MouseButtonEventHandler(this, &LevelEditorWindow::OnMouseUp);

			// Создаем инструменты
			mEntityBrush = gcnew EntityBrush(CommandManager);

			
			mEntityBrush->EntityType = "Cars/Car1";

			//mCurrentBrush = mEntityBrush;

			// Привязываем комманды
			CommandBindings->Add(
				gcnew CommandBinding(SelectEntityBrush, 
				gcnew ExecutedRoutedEventHandler(this, &LevelEditorWindow::ExecutedSelectEntityBrush), 
				gcnew CanExecuteRoutedEventHandler(this, &LevelEditorWindow::CanExecuteSelectEntityBrush)));

			CommandBindings->Add(
				gcnew CommandBinding(AddLayerCommand, 
				gcnew ExecutedRoutedEventHandler(this, &LevelEditorWindow::ExecutedAddLayer), 
				gcnew CanExecuteRoutedEventHandler(this, &LevelEditorWindow::CanExecuteAddLayer)));
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
			switch (msg) 
			{
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
			}
			if (inputSystem->IsKeyDown(HGEK_MBUTTON))
			{
				mouse->button = MouseKey::MiddleButton;
				if (mCurrentBrush != nullptr)
					mCurrentBrush->OnMouseDown(mouse);
			}
			if (inputSystem->IsKeyDown(HGEK_RBUTTON))
			{
				mouse->button = MouseKey::RightButton;
				if (mCurrentBrush != nullptr)
					mCurrentBrush->OnMouseDown(mouse);
			}
			// Отпускание мыши
			if (inputSystem->IsKeyUp(HGEK_LBUTTON))
			{
				mouse->button = MouseKey::LeftButton;
				if (mCurrentBrush != nullptr)
					mCurrentBrush->OnMouseUp(mouse);
			}
			if (inputSystem->IsKeyUp(HGEK_MBUTTON))
			{
				mouse->button = MouseKey::MiddleButton;
				if (mCurrentBrush != nullptr)
					mCurrentBrush->OnMouseUp(mouse);
			}
			if (inputSystem->IsKeyUp(HGEK_RBUTTON))
			{
				mouse->button = MouseKey::RightButton;
				if (mCurrentBrush != nullptr)
					mCurrentBrush->OnMouseUp(mouse);
			}

			// Перемещение мыши
		}

		void LevelEditorWindow::ExecutedSelectEntityBrush( Object^ sender, ExecutedRoutedEventArgs^ e )
		{
			mLevel = gcnew LevelProxy(FactoryManager::GetSingleton()->GetLevel("Level2"));

		//	LayerPtr layer = FactoryManager::GetSingleton()->GetLevel("Level2")->GetLayer("Trees");
			ObjectManager::Instance->Editor = this;
			mEntityBrush->Layer = mLevel->Layers[0];

			mCurrentBrush = mEntityBrush;
		}

		void LevelEditorWindow::CanExecuteSelectEntityBrush( Object^ sender, CanExecuteRoutedEventArgs^ e )
		{
			 e->CanExecute = true;
		}

		void LevelEditorWindow::ExecutedAddLayer( Object^ sender, ExecutedRoutedEventArgs^ e )
		{
			LayerProxy^ layer = gcnew LayerProxy(LayerPtr(new Layer()));
			Commands::AddLayer^ command = gcnew Commands::AddLayer(mLevel, layer);
			CommandManager->Execute(command);
		}

		void LevelEditorWindow::CanExecuteAddLayer( System::Object^ sender, System::Windows::Input::CanExecuteRoutedEventArgs^ e )
		{
			e->CanExecute = true;
		}


		LevelProxy^ LevelEditorWindow::Level::get()
		{
			return mLevel;
		}
	}
}