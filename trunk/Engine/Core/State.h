//  Copyright (C) 2010-2012 Alexander Alimov
//
//	This file is part of Isilme SDK.
//
//		Isilme SDK is free software: you can redistribute it and/or modify
//		it under the terms of the GNU Lesser General Public License as published by
//		the Free Software Foundation, either version 3 of the License, or
//		(at your option) any later version.
//
//		Isilme SDK is distributed in the hope that it will be useful,
//		but WITHOUT ANY WARRANTY; without even the implied warranty of
//		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//		GNU Lesser General Public License for more details.
//
//		You should have received a copy of the GNU Lesser General Public License
//		along with Isilme SDK.  If not, see <http://www.gnu.org/licenses/>.
//
//	Этот файл — часть Isilme SDK.
//
//		Isilme SDK - свободная программа: вы можете перераспространять ее и/или
//		изменять ее на условиях Меньшей стандартной общественной лицензии GNU в том виде,
//		в каком она была опубликована Фондом свободного программного обеспечения;
//		либо версии 3 лицензии, либо (по вашему выбору) любой более поздней
//		версии.
//
//		Isilme SDK распространяется в надежде, что она будет полезной,
//		но БЕЗО ВСЯКИХ ГАРАНТИЙ; даже без неявной гарантии ТОВАРНОГО ВИДА
//		или ПРИГОДНОСТИ ДЛЯ ОПРЕДЕЛЕННЫХ ЦЕЛЕЙ. Подробнее см. в Меньшей стандартной
//		общественной лицензии GNU.
//
//		Вы должны были получить копию Меньшей стандартной общественной лицензии GNU
//		вместе с этой программой. Если это не так, см.
//		<http://www.gnu.org/licenses/>.
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
	gcn::GuiPtr GetGUI();
	
	/// Sets a graphical user interface.
	///
	/// @param [in,out]	gui	If non-null, the graphical user interface.
	void	SetGUI(gcn::GuiPtr gui);
	
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
	
	/// Gets current camera
	CameraPtr	GetCamera();

	/// Sets current camara
	void SetCamera(CameraPtr camera);
private:
	/// Графический интерфейс
	gcn::GuiPtr	mGUI;

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
    gcn::GraphicsPtr graphics;
    /// The input
    gcn::HGEInput* input;
    /// The image loader
    gcn::HGEImageLoader* imageLoader;

	/// Current active camera
	CameraPtr mCamera;
};


#endif