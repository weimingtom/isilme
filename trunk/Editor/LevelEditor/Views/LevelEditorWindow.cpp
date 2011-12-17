#include "Stdafx.h"
#include "LevelEditorWindow.h"
#include "../IsilmeControl.h"
#include "../Commands/NativeCommand.h"
#include "../Editor/AddEntityCommand.h"
#include "../Commands/AddEntity.h"
#include "../Proxy/EntityProxy.h"

namespace LevelEditor
{
	namespace Views
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

			mCurrentBrush = mEntityBrush;
		}

		void LevelEditorWindow::OnMouseDown( Object^ sender, MouseButtonEventArgs^ e )
		{

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
			Vector2 mousePosition = Engine::GetSingleton()->GetInputSystem()->GetMousePosition();
			//Focus();
			if(Engine::GetSingleton()->GetInputSystem()->IsKeyDown(HGEK_LBUTTON))
			{
				mCurrentBrush->OnMouseDown(mousePosition.x, mousePosition.y);
			}
			if (Engine::GetSingleton()->GetInputSystem()->IsKeyUp(HGEK_LBUTTON))
			{
				mCurrentBrush->OnMouseUp(mousePosition.x, mousePosition.y);
				//Vector2 position = Engine::GetSingleton()->GetInputSystem()->GetMousePosition();
				//position.x /= 64;
				//position.y /= 64;

				//LayerPtr layer = FactoryManager::GetSingleton()->GetLevel("Level2")->GetLayer("Trees");
				//EntityPtr entity = FactoryManager::GetSingleton()->CreateEntity("Cars/Car1", "");
				//entity->SetPosition(position);

				//Commands::AddEntity^ command = gcnew Commands::AddEntity(layer, entity);

				//SelectedObject = gcnew Proxy::EntityProxy(entity);
				////command->Execute();
				//CommandManager->Execute(command);

			}
		}

	}
}