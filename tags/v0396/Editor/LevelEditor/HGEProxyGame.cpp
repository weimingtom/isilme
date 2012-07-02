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

	// ������������� ����������� ������
	Engine::GetSingleton()->SetInputSystem(new HGEInputSystem(mHGE));
	Engine::GetSingleton()->SetResourceManager(new HGEResourceManager(mHGE));
	Engine::GetSingleton()->SetSoundSystem(new HGESoundSystem(mHGE));
	Engine::GetSingleton()->mHGE = mHGE;

	// ������������� ��������� ���������
	GetStateManager()->SetRenderer(new HGERenderer(mHGE));
}

void	HGEProxyGame::SetupGUI()
{
}

void	HGEProxyGame::SetupHGE()
{
	// ������� HGE
	if (!(mHGE = hgeCreate(HGE_VERSION)))
	{
		MessageBoxA(0, "���������� ������� ��������� HGE", "������", 0);
		return;
	}

	// ������ ����������
	mHGE->System_SetState(HGE_INIFILE, "HGE.ini");

	bool	windowed = mHGE->Ini_GetInt("VIDEO", "FullScreen", 1) == 0;
	char* res = mHGE->Ini_GetString("VIDEO", "Resolution", "800x600");
	int mWidth = 800;
	int mHeight = 600;
	sscanf_s(res, "%dx%d", &mWidth, &mHeight);
	int		color = mHGE->Ini_GetInt("VIDEO", "Color", 32);
	char*	windowTitle = mHGE->Ini_GetString("WINDOW", "Title", "");

	// �������� ��������� HGE
	mHGE->System_SetState(HGE_LOGFILE, "HGE.log");			// ���
	mHGE->System_SetState(HGE_FRAMEFUNC, FrameFunction);	// ������� �� ����� ����� (�� ���� ��� ���������)
	mHGE->System_SetState(HGE_RENDERFUNC, RenderFunction);	// ������� ��������� �����
	mHGE->System_SetState(HGE_TITLE, windowTitle);			// ��������� ����
	mHGE->System_SetState(HGE_WINDOWED, windowed);			// ������� �����
	mHGE->System_SetState(HGE_SCREENWIDTH, mWidth);			// ������ ����
	mHGE->System_SetState(HGE_SCREENHEIGHT, mHeight);		// ������ ����
	mHGE->System_SetState(HGE_SCREENBPP, color);			// ������� �����
	mHGE->System_SetState(HGE_ZBUFFER, true);				// ������������ Z-�����
	mHGE->System_SetState(HGE_HIDEMOUSE, false);			// �� ������� ����

	// �������������� HGE
	if(!mHGE->System_Initiate())
	{
		mHGE->System_Shutdown();
		mHGE->Release();
		mHGE = NULL;
		MessageBoxA(0, "������ �������������", "������", 0);
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
