#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <stack>
#include <list>
#include <vector>
#include "Definitions.h"

/// @class StateManager
/// Менеджер состояний игры
/// В любой момент времени активно ТОЛЬКО ОДНО состояние
class ISILME_API StateManager
{
public:
	StateManager();
	virtual ~StateManager();

	bool		Update(float elapsedTime);
	bool		Draw(float elapsedTime);
	StatePtr		GetState();
	LevelPtr		GetLevel();
	void		Push(StatePtr state);
	void		Pop();
	Renderer*	GetRenderer();
	void		SetRenderer(Renderer* renderer);
private:
	StateList	mStates;
	StateList	mUpdatedStates;
	lua_State*				mLua;
	Renderer*			mRenderer;
	HGE*				mHGE;
};

#endif