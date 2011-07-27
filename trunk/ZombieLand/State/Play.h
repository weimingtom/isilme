#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include <string>
#include <State.h>
#include <guichan.hpp>
#include "Cameras.h"
#include "Definitions.h"
#include "Engine/GUI/ProgressBar.h"
#include "Engine/GUI/HGELabel.h"

namespace state
{
	/// @class Play
	/// Игровая сцена
	class Play : public State, public gcn::MouseListener
	{
	public:
		Play();

		void mousePressed(gcn::MouseEvent& mouseEvent){}
   
		void mouseReleased(gcn::MouseEvent& mouseEvent){}

		void mouseClicked(gcn::MouseEvent& mouseEvent);

		void mouseMoved(gcn::MouseEvent& mouseEvent){}

		void mouseEntered(gcn::MouseEvent& mouseEvent){}

		void mouseExited(gcn::MouseEvent& mouseEvent){}

		void mouseWheelMovedDown(gcn::MouseEvent& mouseEvent){}

		void mouseWheelMovedUp(gcn::MouseEvent& mouseEvent){}

		void mouseDragged(gcn::MouseEvent& mouseEvent){}
	
		virtual ~Play()
		{
		}

	protected:
		virtual void OnStart();

		gcn::Button* mOptions;
		gcn::Button* mContinue;
		gcn::Button* mSave;
		gcn::Button* mExit;
		gcn::Window* mMenu;
		gcn::Button* mRestart;
		gcn::Label* mHealthField;
		gcn::Icon*			mHealthImage;
		gcn::ImageButton*	mAmmo1Button;
		gcn::ImageButton*	mAmmo2Button;
		gcn::ImageButton*	mAmmo3Button;
		gcn::ImageButton*	mAmmo4Button;
		gcn::ImageButton*	mAbility1Button;
		gcn::ImageButton*	mAbility2Button;
		gcn::ImageButton*	mAbility3Button;
		gcn::ImageButton*	mAbility4Button;

		gcn::Icon*			mOrbImage;
		gcn::Label*			mOrbLabel;
		gcn::ProgressBar*	mHealthBar;
		gcn::ProgressBar*	mEnergyBar;
		gcn::HGELabel*			mZombieLeftLabel;

		gcn::Icon*			mWeaponIcon;
		gcn::ProgressBar*	mWeaponAmmo;
		behaviour::PlayerPtr mPlayer;

		virtual void OnUpdate(float elapsedTime);

		bool	isReloading;
		bool	isChangingWeapon;
	};
};

#endif