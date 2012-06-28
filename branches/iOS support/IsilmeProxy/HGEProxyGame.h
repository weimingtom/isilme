#pragma once

#include <Isilme.h>

class HGEProxyGame : public Game
{
public:
	/// Default constructor.
	HGEProxyGame();
	/// Destructor.
	virtual ~HGEProxyGame();

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

