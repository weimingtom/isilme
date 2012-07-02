#include "Stdafx.h"
#include "HGEProxyGame.h"


HGEProxyGame::HGEProxyGame()
{
	InitEngine();
}

HGEProxyGame::~HGEProxyGame()
{
}

void	HGEProxyGame::InitEngine()
{
	SetupHGE();
	SetupGUI();

	// Инициализация компонентов движка
	Engine::GetSingleton()->SetInputSystem(new HGEInputSystem(mHGE));
	Engine::GetSingleton()->SetResourceManager(new HGEResourceManager(mHGE));
	Engine::GetSingleton()->SetSoundSystem(new HGESoundSystem(mHGE));
	Engine::GetSingleton()->mHGE = mHGE;

	// Инициализация менеджера состояний
	GetStateManager()->SetRenderer(new HGERenderer(mHGE));
}

void	HGEProxyGame::SetupGUI()
{
}

void	HGEProxyGame::SetupHGE()
{
	// Создаем HGE
	if (!(mHGE = hgeCreate(HGE_VERSION)))
	{
		MessageBoxA(0, "Невозможно создать интерфейс HGE", "Ошибка", 0);
		return;
	}

	// Читаем прараметры
	mHGE->System_SetState(HGE_INIFILE, "HGE.ini");

	bool	windowed = mHGE->Ini_GetInt("VIDEO", "FullScreen", 1) == 0;
	char* res = mHGE->Ini_GetString("VIDEO", "Resolution", "800x600");
	int mWidth = 800;
	int mHeight = 600;
	sscanf_s(res, "%dx%d", &mWidth, &mHeight);
	int		color = mHGE->Ini_GetInt("VIDEO", "Color", 32);
	char*	windowTitle = mHGE->Ini_GetString("WINDOW", "Title", "");

	// Проводим настройку HGE
	mHGE->System_SetState(HGE_LOGFILE, "HGE.log");			// Лог
	mHGE->System_SetState(HGE_FRAMEFUNC, FrameFunction);	// Функция во время кадра (Не знаю как перевести)
	mHGE->System_SetState(HGE_RENDERFUNC, RenderFunction);	// Функция рисования сцены
	mHGE->System_SetState(HGE_TITLE, windowTitle);			// Заголовок окна
	mHGE->System_SetState(HGE_WINDOWED, windowed);			// Оконный режим
	mHGE->System_SetState(HGE_SCREENWIDTH, mWidth);			// Ширина окна
	mHGE->System_SetState(HGE_SCREENHEIGHT, mHeight);		// Высота окна
	mHGE->System_SetState(HGE_SCREENBPP, color);			// Глубина цвета
	mHGE->System_SetState(HGE_ZBUFFER, true);				// Использовать Z-буфер
	mHGE->System_SetState(HGE_HIDEMOUSE, false);			// Не прятать мышь

	// Инициализируем HGE
	if(!mHGE->System_Initiate())
	{
		mHGE->System_Shutdown();
		mHGE->Release();
		mHGE = NULL;
		MessageBoxA(0, "Ошибка инициализации", "Ошибка", 0);
		return;
	}

}

void	HGEProxyGame::Start()
{
	mHGE->System_Start();
}

bool	HGEProxyGame::FrameFunction()
{
	HGE* hge = ((HGEGame*)Game::GetSingleton())->GetHGE();
	return mInstance->GetStateManager()->Update(hge->Timer_GetDelta());
}

bool	HGEProxyGame::RenderFunction()
{
	HGE* hge = ((HGEGame*)Game::GetSingleton())->GetHGE();
	HGEGame::mInstance->GetStateManager()->Draw(hge->Timer_GetDelta());
	return true;
}
