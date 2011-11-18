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
	/// Редактор уровняф
	class Editor : public State, public gcn::MouseListener
	{
	public:
		Editor();

		/// Устанавливает кисть объектов как текущий инструмент
		void	SelectEntityBrushTool();

		/// Установить текущий инструмент - выбор объектов
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
		gcn::HGELabel*		mSpellAmmo;
		gcn::HGELabel*		mAmmoLabel;
		gcn::Icon*			mSpellIcon;
		behaviour::CreaturePtr mPlayer;
		
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
	private:
		/// Текущий инструмент
		editor::ToolPtr	mCurrentTool;

		/// Кисть объектов
		editor::EntityBrushToolPtr mEntityBrush;

		/// Инструмент выбора объектов
		editor::SelectorToolPtr mSelectorTool;

		/// Выбранный слой
		LayerPtr mSelectedLayer;

		editor::CommandManagerPtr mCommandManager;
	};
};

#endif