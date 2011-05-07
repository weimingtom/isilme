#include "Isilme.h"

StateManager::StateManager() :
	mRenderer(0),
	mLua(0)
{
}

StateManager::~StateManager()
{
}

void		StateManager::Pop()
{
	mStates.pop_back();
}

void		StateManager::Push(StatePtr state)
{
	mStates.push_back(state);
	state->Start();
}

StatePtr		StateManager::GetState()
{
	return mStates.back();
}

LevelPtr		StateManager::GetLevel()
{
	return mStates.back()->GetLevel();
}

bool		StateManager::Update(float elapsedTime)
{
	if (!mStates.back()->Update(elapsedTime))
		mStates.pop_back();

	return mStates.size() == 0;
}

bool		StateManager::Draw(float elapsedTime)
{
	mRenderer->BeginScene();

	// Рисуем уровень
	mRenderer->Draw(mStates.back()->GetLevel());

	// Рисуем интерфейс
	mStates.back()->GetGUI()->draw();

	mRenderer->EndScene();
	
	return false;
}

Renderer*	StateManager::GetRenderer()
{
	return mRenderer;
}

void		StateManager::SetRenderer(Renderer* renderer)
{
	mRenderer = renderer;
}