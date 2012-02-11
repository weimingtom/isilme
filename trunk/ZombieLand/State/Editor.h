#ifndef EDITORSTATE_H
#define EDITORSTATE_H

#include <string>
#include <State.h>
#include <guichan.hpp>
#include "Cameras.h"
#include "Definitions.h"
#include "Engine/GUI/ProgressBar.h"
#include "Engine/GUI/HGELabel.h"
#include "Engine/GUI/QuestBook.h"
#include "Engine/Quest/Quests.h"
#include "Engine/Editor/EditorDefinitions.h"

namespace state
{
	/// @class Editor
	/// �������� �������
	class Editor : public State, public gcn::MouseListener
	{
	public:
		Editor();

		/// ������������� ����� �������� ��� ������� ����������
		void	SelectEntityBrushTool();

		/// ���������� ������� ���������� - ����� ��������
		void	SelectSelectorTool();

		void mousePressed(gcn::MouseEvent& mouseEvent);
   
		void mouseReleased(gcn::MouseEvent& mouseEvent);

		void mouseClicked(gcn::MouseEvent& mouseEvent);

		void mouseMoved(gcn::MouseEvent& mouseEvent){}

		void mouseEntered(gcn::MouseEvent& mouseEvent){}

		void mouseExited(gcn::MouseEvent& mouseEvent){}

		void mouseWheelMovedDown(gcn::MouseEvent& mouseEvent){}

		void mouseWheelMovedUp(gcn::MouseEvent& mouseEvent){}

		void mouseDragged(gcn::MouseEvent& mouseEvent){}
	
		virtual ~Editor()
		{
		}

		editor::CommandManagerPtr GetCommandManager();
	protected:
		void	OnSetStage(story::QuestPtr quest, int stage);
		virtual void OnStart();

		gcn::ButtonPtr mOptions;
		gcn::ButtonPtr mContinue;
		gcn::ButtonPtr mSave;
		gcn::ButtonPtr mExit;
		gcn::WindowPtr mMenu;
		gcn::ButtonPtr mRestart;
		gcn::LabelPtr mHealthField;
		gcn::IconPtr			mHealthImage;

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

		virtual void OnUpdate(float elapsedTime);

		bool	isReloading;
		bool	isChangingWeapon;
		bool	isChangingSpell;
		bool	isSpellCasting;
		bool	isShooting;

		bool	Asking;
	private:
		/// ������� ����������
		editor::ToolPtr	mCurrentTool;

		/// ����� ��������
		editor::EntityBrushToolPtr mEntityBrush;

		/// ���������� ������ ��������
		editor::SelectorToolPtr mSelectorTool;

		/// ��������� ����
		LayerPtr mSelectedLayer;

		editor::CommandManagerPtr mCommandManager;
	};
};

#endif