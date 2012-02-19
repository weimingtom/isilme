#include "IsilmePCH.h"
#include "State.h"
#include "Level.h"

State::State()
{
	mCamera = CameraPtr(new Camera());
	isPaused = false;
	mGUI = gcn::GuiPtr(new gcn::Gui());
	mPausePrev = true;
	isTransporate = true;
	isClosed = false;
	mLevel = LevelPtr(new Level());


	// Init GUI
	imageLoader = new gcn::HGEImageLoader();

	gcn::Image::setImageLoader(imageLoader);
	graphics = gcn::GraphicsPtr(new gcn::HGEGraphics());
	input = new gcn::HGEInput();
    
	mGUI->SetGraphics(graphics);
	mGUI->SetInput(input);
}

void	State::SetLevel(LevelPtr level)
{
	mLevel = level;
}

bool	State::IsPaused()
{
	return isPaused;
}

void	State::SetPaused(bool pause)
{
	isPaused = pause;
}

void	State::SetGUI(gcn::GuiPtr gui)
{
	mGUI = gui;
}

gcn::GuiPtr State::GetGUI()
{
	return mGUI;
}

void State::Start()
{
	isClosed = false;
	OnStart();
}
void State::Close()
{
	isClosed = true;
}

bool State::Update(float elapsedTime)
{
	if (mGUI)
		mGUI->Logic();

	if (!isPaused)
	{
		mLevel->Update(elapsedTime);
	}

	if (mCamera)
		mCamera->Update(elapsedTime);

	OnUpdate(elapsedTime);
	return !isClosed;
}
bool State::Draw(float elapsedTime)
{
	
	return false;
}

State::~State() 
{
}

bool State::IsTransporate()
{
	return isTransporate;
}

void State::SetTransporate(bool value)
{
	isTransporate = value;
}
bool State::GetPausePrev()
{
	return mPausePrev;
}
void State::SetPausePrev(bool value)
{
	mPausePrev = value;
}
void State::OnUpdate(float elapsedTime)
{
}
void State::OnStart() 
{
	isClosed = false;
}
void State::OnResume() 
{
}
void State::OnDraw()
{
}
LevelPtr State::GetLevel()
{
	return mLevel;
}

CameraPtr State::GetCamera()
{
	return mCamera;
}

void State::SetCamera(CameraPtr camera)
{
	mCamera = camera;
}