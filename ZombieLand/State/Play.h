#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include <string>
#include <State.h>
#include <guichan.hpp>
#include "Cameras.h"
#include "Definitions.h"
#include "Engine/GUI/ProgressBar.h"
#include "Engine/GUI/HGELabel.h"
#include "Engine/GUI/QuestBook.h"

namespace state
{
	/// @class Play
	/// ������� �����
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

		gcn::Icon*			mOrbImage;
		gcn::Label*			mOrbLabel;
		gcn::ProgressBar*	mHealthBar;
		gcn::ProgressBar*	mEnergyBar;
		gcn::HGELabel*			mZombieLeftLabel;

		gcn::Icon*			mWeaponIcon;
		gcn::HGELabel*		mWeaponAmmo;
		gcn::HGELabel*		mAmmoLabel;
		gcn::Icon*			mSpellIcon;
		behaviour::PlayerPtr mPlayer;
		
		gcn::Container* top;
		gcn::Window* mRespawn;
		gcn::Button* mRRestart;
		gcn::Button* mRRespawn;
		gcn::Button* mRMenu;
		gcn::QuestBook* mQuestBook;

		virtual void OnUpdate(float elapsedTime);

		bool	isReloading;
		bool	isChangingWeapon;
		bool	isChangingSpell;
		bool	isSpellCasting;
		bool	isShooting;

		bool	Asking;
	};
};

#endif