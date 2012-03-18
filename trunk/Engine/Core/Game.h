#ifndef GAME_H
#define GAME_H

#include <hge.h>
#include "Definitions.h"
#include "Engine/Story/Quests.h"

class ISILME_API Game
{
public:
	Game();
	virtual ~Game();

	virtual void		Init() = 0;
	virtual void		Start() = 0;
	StateManager*		GetStateManager();
	story::StoryPtr		GetStory();
	static Game*		GetSingleton();
	bool GetUsePhisics();
	void SetUsePhisics(bool value);
protected:
	virtual void		InitEngine() = 0;
	story::StoryPtr		mStory;
	static	Game*		mInstance;
private:
	StateManager*		mStateManager;
	bool mUsePhisics;
};

/// Hge game.
class ISILME_API HGEGame : public Game
{
public:
	HGEGame(HGE* hge);

	/// Default constructor.
	HGEGame();
	/// Destructor.
	virtual ~HGEGame();

	/// Initialises this object.
	virtual void		Init() = 0;
	/// Starts this object.
	void				Start();

	HGE*				GetHGE() {return mHGE;};
protected:
	/// Initialises the engine.
	virtual void		InitEngine();
	/// The hge
	HGE*				mHGE;

private:
	/// Sets up the hge.
	void				SetupHGE();
	/// Sets up the graphical user interface.
	void				SetupGUI();
public:
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