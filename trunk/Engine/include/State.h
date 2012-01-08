#ifndef STATE_H
#define STATE_H

#include "Level.h"
#include <guichan.hpp>
#include <guichan/hge.hpp>



/// Состояние игры.
///  Состояние игры представляет собой сцену уровня и графический интерфейс
/// уровня.
class ISILME_API State
{
public:	
	/// Default constructor.
	State();
	
	/// Destructor.
	virtual ~State();
	
	/// Gets the graphical user interface.
	///
	/// @return	null if it fails, else the graphical user interface.
	gcn::Gui* GetGUI();
	
	/// Sets a graphical user interface.
	///
	/// @param [in,out]	gui	If non-null, the graphical user interface.
	void	SetGUI(gcn::Gui* gui);
	
	/// Query if this object is paused.
	///
	/// @return	true if paused, false if not.
	bool IsPaused();
	
	/// Sets a paused.
	///
	/// @param	pause	true to pause.
	void SetPaused(bool pause);
	
	/// Starts this object.
	void Start();
	
	/// Closes this object.
	void Close();
	
	/// Updates the given elapsedTime.
	///
	/// @param	elapsedTime	Time of the elapsed.
	///
	/// @return	true if it succeeds, false if it fails.
	bool Update(float elapsedTime);
	
	/// Draws.
	///
	/// @param	elapsedTime	Time of the elapsed.
	///
	/// @return	true if it succeeds, false if it fails.
	virtual bool Draw(float elapsedTime);	
	
	/// Query if this object is transporate.
	///
	/// @return	true if transporate, false if not.
	bool IsTransporate();	
	
	/// Sets a transporate.
	///
	/// @param	value	true to value.
	void SetTransporate(bool value);
	
	/// Gets the previous item.
	///
	/// @return	true if it succeeds, false if it fails.
	bool GetPausePrev();
	
	/// Sets a pause previous.
	///
	/// @param	value	true to value.
	void SetPausePrev(bool value);
	
	/// Gets the level.
	///
	/// @return	The level.
	LevelPtr GetLevel();	
	
	/// Sets a level.
	///
	/// @param	level	The level.
	void	SetLevel(LevelPtr level);

	/// Executes the update action.
	///
	/// @param	elapsedTime	Time of the elapsed.
	virtual void OnUpdate(float elapsedTime);
	
	/// Executes the start action.
	virtual void OnStart();	
	
	/// Executes the resume action.
	virtual void OnResume();
	
	/// Executes the draw action.
	virtual void OnDraw();
	
private:
	/// Графический интерфейс
	gcn::Gui*	mGUI;

	/// true to pause previous
	bool mPausePrev;
	/// true if this object is paused
	bool isPaused;
	/// true if this object is transporate
	bool isTransporate;

	/// Флаг закрытия состояния
	bool isClosed;

	/// Уровень состояния
	LevelPtr mLevel;

    /// The graphics
    gcn::HGEGraphics* graphics;
    /// The input
    gcn::HGEInput* input;
    /// The image loader
    gcn::HGEImageLoader* imageLoader;
};


#endif