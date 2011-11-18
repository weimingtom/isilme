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

/// Hge game.
class IsilmeExport HGEGame : public Game
{
public:
	/// Default constructor.
	HGEGame();
	/// Destructor.
	virtual ~HGEGame();

	/// Initialises this object.
	virtual void		Init() = 0;
	/// Starts this object.
	void				Start();
protected:
	/// Initialises the engine.
	virtual void		InitEngine();
	///< The hge
	HGE*				mHGE;

private:
	/// Sets up the hge.
	void				SetupHGE();
	/// Sets up the graphical user interface.
	void				SetupGUI();
	/// Renders the function.
	///
	/// @return	true if it succeeds, false if it fails.
	static	bool		RenderFunction();
	/// Gets the frame function.
	///
	/// @return	true if it succeeds, false if it fails.
	static	bool		FrameFunction();
};
#endif