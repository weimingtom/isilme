#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <stack>
#include <list>
#include <vector>
#include <LuaCPP.h>
#include "Definitions.h"

/// @class StateManager
/// Менеджер состояний игры
/// В любой момент времени активно ТОЛЬКО ОДНО состояние
class IsilmeExport StateManager
{
public:
	StateManager();
	virtual ~StateManager();

	bool		Update(float elapsedTime);
	bool		Draw(float elapsedTime);
	State*		GetState();
	LevelPtr		GetLevel();
	void		Push(State* state);
	void		Pop();
	Renderer*	GetRenderer();
	void		SetRenderer(Renderer* renderer);
private:
	std::list <State*>	mStates;
	std::list <State*>	mUpdatedStates;
	Lua*				mLua;
	Renderer*			mRenderer;
	HGE*				mHGE;
};

#endif