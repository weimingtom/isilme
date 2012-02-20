#include "StdAfx.h"
#include "IsilmeControl.h"
#include <hge.h>
#include "../Editor/Command.h"
#include "../Editor/CommandManager.h"
#include "../Editor/EditorDefinitions.h"
#include "../Editor/AddEntityCommand.h"
#include <vcclr.h>
#include "Commands/NativeCommand.h"
#include "View/EntityPaletteTool.h"
#include "Proxy/EntityPaletteProxy.h"
#include "View/LevelEditorWindow.h"
#include "IsilmeProxy.h"
#include "Proxy/ModuleProxy.h"
#include "Engine/Core/MasterFile.h"
#include "Engine/Quest/Story.h"
#include "Proxy/StoryProxy.h"

using namespace System::Threading;

namespace LevelEditor
{
	public ref class StoryConverter : public Proxy::IDataToProxyConverter
	{
	public:
		virtual Common::IProxyObject^ Convert(SharedCLIPtr<Entry>* entry)
		{
			story::StoryPtr story = boost::shared_dynamic_cast<StoryEntry>(entry->Value)->data;
			return gcnew Proxy::StoryProxy(story);
		}
	};

	class EditorState : public State
	{
	public:
		gcroot<IsilmeHost^> host;

		EditorState() :
			mCommandManager(new editor::CommandManager())
		{
			gcn::ContainerPtr top(new gcn::Container());
			GetGUI()->SetTop(top);
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

		void PreInit()
		{
		
		}
		virtual void Init()
		{
			// Register converters to Proxy
			GameDataToProxyConverter::RegisterConverter("Levels", gcnew LevelDataToProxyConverter());
			GameDataToProxyConverter::RegisterConverter("Story", gcnew StoryConverter());

			mHGE->System_Initiate();
			EditorState* estate = new EditorState();
			StatePtr state(estate);

			FactoryManager::GetSingleton()->LoadMasterFile("../Data/Master.imf");
			//FactoryManager::GetSingleton()->LoadGraphics("../Data/Graphics.xml");
			//FactoryManager::GetSingleton()->LoadEntities("../Data/Entities.xml");
			LevelEditor::View::EntityPaletteTool::Instance->Palette = gcnew EntityPaletteProxy(FactoryManager::GetSingleton()->GetEntityPalette());
			//FactoryManager::GetSingleton()->LoadLevel("../Data/TestL.xml");
			//LevelPtr level = FactoryManager::GetSingleton()->GetLevel("Level2");//new Level());
			//CameraPtr camera(new Camera());
			//camera->x = 0.0f;
			//camera->y = 0.0f;
			////level->Load("../Data/TestL.xml");
			//level->SetActiveCamera(camera);
			//state->SetLevel(level);
			
			GetStateManager()->Push(state);
			Isilme::Instance->RaiseLoaded();
			LevelEditor::View::LevelEditorWindow::Instance->Load();
			SetUsePhisics(false);
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


		_hge = hgeCreate(HGE_VERSION);


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
		if (msg == WM_COMMAND)
		{
		
		}
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

	void IsilmeHost::LoadGameData()
	{
		if (_hge)
			return;

		_hge = hgeCreate(HGE_VERSION);


		_hge->System_SetState(HGE_SCREENWIDTH, 640);
		_hge->System_SetState(HGE_SCREENHEIGHT, 480);
		_hge->System_SetState(HGE_SCREENBPP, 32);
		_hge->System_SetState(HGE_FPS, 60);
		_hge->System_SetState(HGE_WINDOWED, true);
		_hge->System_SetState(HGE_DONTSUSPEND, true);
		_hge->System_SetState(HGE_SHOWSPLASH, false);
		_hge->System_SetState(HGE_USESOUND, false);
		//_hge->System_SetState(HGE_HWNDPARENT, handle);

		new EditorGame(_hge);

		LevelEditor::View::EntityPaletteTool::Instance->Palette = gcnew EntityPaletteProxy(FactoryManager::GetSingleton()->GetEntityPalette());
	}

	void IsilmeHost::Resize( int width, int height )
	{
	//	_hge->System_SetState(HGE_SCREENWIDTH, width);
	//	_hge->System_SetState(HGE_SCREENHEIGHT, height);

		MoveWindow(_hge->System_GetState(HGE_HWND),
			0, 0, width, height, true);
		Width = width;
		Height = height;
	}

};
