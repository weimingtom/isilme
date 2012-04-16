//  Copyright (C) 2010-2012 VSTU
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