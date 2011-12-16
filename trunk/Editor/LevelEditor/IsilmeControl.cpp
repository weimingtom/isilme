#include "StdAfx.h"
#include "IsilmeControl.h"
#include <hge.h>
#include "../Editor/Command.h"
#include "../Editor/CommandManager.h"
#include "../Editor/EditorDefinitions.h"
#include "../Editor/AddEntityCommand.h"
#include <vcclr.h>
#include "Commands/NativeCommand.h"

using namespace System::Threading;

namespace LevelEditor
{
	class EditorState : public State
	{
	public:
		gcroot<IsilmeHost^> host;

		EditorState() :
			mCommandManager(new editor::CommandManager())
		{
			gcn::Container* top = new gcn::Container();
			GetGUI()->setTop(top);
		}

		virtual void OnUpdate(float elapsedTime)
		{
			host->OnUpdate(elapsedTime);
		}
	private:
		editor::CommandManagerPtr mCommandManager;
	};
	class EditorGame : public HGEGame
	{
	public:
		EditorGame()
		{
		}
		EditorGame(HGE* hge) : HGEGame(hge)
		{
		
		}

		virtual void Init()
		{
			EditorState* estate = new EditorState();
			StatePtr state(estate);
			FactoryManager::GetSingleton()->LoadGraphics("../Data/TestG.xml");
			FactoryManager::GetSingleton()->LoadEntities("../Data/TestE.xml");

			FactoryManager::GetSingleton()->LoadLevel("../Data/TestL.xml");
			LevelPtr level = FactoryManager::GetSingleton()->GetLevel("Level2");//new Level());
			CameraPtr camera(new Camera());
			camera->x = 0.0f;
			camera->y = 0.0f;
			//level->Load("../Data/TestL.xml");
			level->SetActiveCamera(camera);
			state->SetLevel(level);
			
			GetStateManager()->Push(state);
		}
	};
	IsilmeHost::IsilmeHost()
	{


	}

	void IsilmeHost::Start()
	{
		ComponentDispatcher::RaiseIdle();
	}

	HandleRef IsilmeHost::BuildWindowCore( HandleRef hwndParent )
	{
		HWND handle = CreateWindowEx(0, L"static", 
			L"this is a Win32 listbox",
			WS_CHILD | WS_VISIBLE ,
			0, 0, // x, y
			640, 480, // height, width
			(HWND) hwndParent.Handle.ToPointer(), // parent hwnd
			0, // hmenu
			0, // hinstance
			0); // lparam


		HGE* _hge = hgeCreate(HGE_VERSION);


		_hge->System_SetState(HGE_SCREENWIDTH, 640);
		_hge->System_SetState(HGE_SCREENHEIGHT, 480);
		_hge->System_SetState(HGE_SCREENBPP, 32);
		_hge->System_SetState(HGE_FPS, 60);
		_hge->System_SetState(HGE_WINDOWED, true);
		_hge->System_SetState(HGE_DONTSUSPEND, true);
		_hge->System_SetState(HGE_SHOWSPLASH, false);
		_hge->System_SetState(HGE_USESOUND, false);
		_hge->System_SetState(HGE_HWNDPARENT, handle);

		Game* game = new EditorGame(_hge);
		game->Init();
		((EditorState*)game->GetStateManager()->GetState().get())->host = this;

		ComponentDispatcher::ThreadIdle += gcnew EventHandler(this, &IsilmeHost::OnThreadIdle);
	//	game->Start();
		//HGEGame::RenderFunction();
		//HGEGame::FrameFunction();
		return HandleRef(this, IntPtr(handle));
	}

	void IsilmeHost::DestroyWindowCore( HandleRef hwndParent )
	{

	}

	System::IntPtr IsilmeHost::WndProc( IntPtr hwnd, int msg, IntPtr wParam, IntPtr lParam, bool handled )
	{
		HGEGame::RenderFunction();
		HGEGame::FrameFunction();

		return IntPtr::Zero;
	}

	void IsilmeHost::OnThreadIdle( Object^ sender, EventArgs^ e )
	{
		HGEGame::GetSingleton()->Start();

		Dispatcher->BeginInvoke(System::Windows::Threading::DispatcherPriority::ApplicationIdle,  gcnew ThreadStart(this, & IsilmeHost::Start));
	}

	void IsilmeHost::OnUpdate( float elapsedTime )
	{
		if (UpdateFrame != nullptr)
		{
			UpdateFrame(elapsedTime)	;
		}
	}

};
