#include "Isilme.h"

State::State()
{
	isPaused = false;
	mGUI = new gcn::Gui();
	mPausePrev = true;
	isTransporate = true;
	isClosed = false;
	mLevel = LevelPtr(new Level());


	// Init GUI
	imageLoader = new gcn::HGEImageLoader();

	gcn::Image::setImageLoader(imageLoader);
	graphics = new gcn::HGEGraphics();
	input = new gcn::HGEInput();
    
	mGUI->setGraphics(graphics);
	mGUI->setInput(input);
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

void	State::SetGUI(gcn::Gui* gui)
{
	mGUI = gui;
}

gcn::Gui* State::GetGUI()
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
		mGUI->logic();

	if (!isPaused)
	{
		mLevel->Update(elapsedTime);
	}

	OnUpdate(elapsedTime);
	return !isClosed;
}
bool State::Draw(float elapsedTime)
{
	
	return false;
}

State::~State() 
{
	delete mGUI;
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