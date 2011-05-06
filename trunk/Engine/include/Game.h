#ifndef GAME_H
#define GAME_H

#include <hge.h>
#include "Definitions.h"
#include "Engine/Quest/Quests.h"

class IsilmeExport Game
{
public:
	Game();
	virtual ~Game();

	virtual void		Init() = 0;
	virtual void		Start() = 0;
	StateManager*		GetStateManager();
	story::StoryPtr		GetStory();
	static Game*		GetSingleton();
protected:
	virtual void		InitEngine() = 0;
	story::StoryPtr		mStory;
	static	Game*		mInstance;
private:
	StateManager*		mStateManager;
};

class IsilmeExport HGEGame : public Game
{
public:
	HGEGame();
	virtual ~HGEGame();

	virtual void		Init() = 0;
	void				Start();
protected:
	virtual void		InitEngine();
	HGE*				mHGE;

private:
	void				SetupHGE();
	void				SetupGUI();
	static	bool		RenderFunction();
	static	bool		FrameFunction();
};
#endif