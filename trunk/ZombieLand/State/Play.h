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
#include "Engine/GUI/InventoryWindow.h"
#include "Engine/GUI/ConversationWindow.h"
#include "Engine/Quest/Quests.h"1

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
		void	OnSetStage(story::QuestPtr quest, int stage);
		virtual void OnStart();

		gcn::ButtonPtr mOptions;
		gcn::ButtonPtr mContinue;
		gcn::ButtonPtr mSave;
		gcn::ButtonPtr mExit;
		gcn::WindowPtr mMenu;
		gcn::ButtonPtr mRestart;
		gcn::LabelPtr	mHealthField;
		gcn::IconPtr	mHealthImage;

		gcn::IconPtr			mOrbImage;
		gcn::LabelPtr			mOrbLabel;
		gcn::ProgressBarPtr	mHealthBar;
		gcn::ProgressBarPtr	mEnergyBar;
		gcn::LabelPtr			mZombieLeftLabel;

		gcn::IconPtr			mWeaponIcon;
		gcn::LabelPtr		mWeaponAmmo;
		gcn::LabelPtr		mSpellAmmo;
		gcn::LabelPtr		mAmmoLabel;
		gcn::IconPtr			mSpellIcon;
		behaviour::CreaturePtr mPlayer;
		
		gcn::ContainerPtr top;
		gcn::WindowPtr mRespawn;
		gcn::ButtonPtr mRRestart;
		gcn::ButtonPtr mRRespawn;
		gcn::ButtonPtr mRMenu;
		gcn::QuestBookPtr mQuestBook;
		gcn::ConversationWindowPtr mConversationWindow;
		gcn::InventoryWindowPtr mInventoryWindow;

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