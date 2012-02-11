#include "ZombieLand.h"
#include "FactoryManager.h"
#include "Engine/Quest/Story.h"
#include "Engine/Quest/Quest.h"
#include "Engine/Quest/Stage.h"
#include <string>
#include <guichan.hpp>
#include "Editor.h"
#include "ZombieLand/Behaviour/Creature.h"
#include "Engine/GUI/ProgressBar.h"
#include "Engine/GUI/QuestBook.h"
#include <luabind/function.hpp>
#include "Engine/Quest/Quest.h"
#include "Engine/Quest/Stage.h"
#include "Engine/Editor/EntityBrushTool.h"
#include "Engine/Editor/CommandManager.h"
#include "Engine/Core/Serialisation/StaticLevelSerialiser.h"
namespace state
{

	void	Editor::OnSetStage(story::QuestPtr quest, int stage)
	{
		mZombieLeftLabel->setCaption(quest->GetStage(stage)->GetText());
	}

Editor::Editor() : State()
{	
	mCommandManager.reset(new editor::CommandManager());
	isReloading = false;
	isChangingWeapon = false;
	isChangingSpell = false;
	isSpellCasting = false;
	// Init GUI
	//
	top = gcn::ContainerPtr(new gcn::Container());
    // We set the dimension of the top container to match the screen.
    top->SetDimension(gcn::Rectangle(0, 0, 800, 600));
	top->setBackgroundColor(gcn::Color(0,0,0,0));
	top->setBaseColor(gcn::Color(0,0,0,0));
	top->SetFocusable(true);
	gcn::FontPtr font = gcn::FontPtr(new gcn::HGEImageFont("../Data/Fonts/font1.fnt"));//new gcn::ImageFont("../Data/Fonts/fixedfont.bmp", " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
	gcn::Widget::SetGlobalFont(font);
    // Finally we pass the top widget to the Gui object.
    GetGUI()->SetTop(top);
	
	// ��������
	mMenu		= gcn::WindowPtr(new gcn::Window());
	mContinue	= gcn::ButtonPtr(new gcn::Button());
	mSave		= gcn::ButtonPtr(new gcn::Button());
	mRestart	= gcn::ButtonPtr(new gcn::Button());
	mOptions	= gcn::ButtonPtr(new gcn::Button());
	mExit		= gcn::ButtonPtr(new gcn::Button());

	mRespawn	= gcn::WindowPtr(new gcn::Window());
	mRRestart	= gcn::ButtonPtr(new gcn::Button());
	mRRespawn	= gcn::ButtonPtr(new gcn::Button());
	mRMenu		= gcn::ButtonPtr(new gcn::Button());

	mHealthImage	= gcn::IconPtr(new gcn::Icon());
	mHealthField	= gcn::LabelPtr(new gcn::Label("none"));
	mAmmoLabel		= gcn::LabelPtr(new gcn::Label("../Data/Fonts/font1.fnt"));
	mWeaponIcon		= gcn::IconPtr(new gcn::Icon());
	mWeaponAmmo		= gcn::LabelPtr(new gcn::Label("../Data/Fonts/font1.fnt"));
	mSpellIcon		= gcn::IconPtr(new gcn::Icon());
	mSpellAmmo		= gcn::LabelPtr(new gcn::Label("../Data/Fonts/font1.fnt"));

	mQuestBook		= gcn::QuestBookPtr(new gcn::QuestBook());

	mQuestBook->SetVisible(false);

	// ������ �����������
	mSpellIcon->SetSize(64, 64);
	mSpellIcon->setImage(gcn::Image::load("../Data/Icons/Empty.png"));

	// ������ ��������
	mHealthImage->setImage(gcn::Image::load("../Data/Textures/Icons/Health.png"));
	mHealthImage->SetSize(64, 64);

	// ������ ������
	mWeaponIcon->setImage(gcn::Image::load("../Data/Icons/Empty.png"));
	mWeaponIcon->SetSize(64, 64);

	// ������� ������
	//mWeaponAmmo->setTextColor(gcn::Color(255,255,255));

	// ���������� ����������
	//mSpellAmmo->setTextColor(gcn::Color(255,255,255));

	// ���������� ��������
	//mAmmoLabel->setTextColor(gcn::Color(255, 255, 255));
	
	// ������ �������
	mOrbImage = gcn::IconPtr(new gcn::Icon("../Data/Textures/Icons/Orb.png"));
	mOrbImage->SetSize(64, 64);

	// ���������� �������
	mOrbLabel = gcn::LabelPtr(new gcn::Label("x"));

	// ���������� �����
	mZombieLeftLabel = gcn::LabelPtr(new gcn::Label());
	//mZombieLeftLabel->setTextColor(gcn::Color(200, 200, 200));
	//mZombieLeftLabel->setForegroundColor(gcn::Color(200, 200, 200));

	// ���������� ����
	mContinue->setCaption("Continue");
	mContinue->SetSize(150, 20);
//	mContinue->addMouseListener(this);

	// ��������� ����
	mSave->setCaption("Save");
	mSave->SetSize(150, 20);
//	mSave->addMouseListener(this);

	// �����
	mOptions->setCaption("Options");
	mOptions->SetSize(150, 20);
//	mOptions->addMouseListener(this);

	// ��������� �������
	mExit->setCaption("Exit to menu");
	mExit->SetSize(150, 20);
//	mExit->addMouseListener(this);

	// ������ �������
	mRestart->setCaption("Restart");
	mRestart->SetSize(150, 20);
//	mRestart->addMouseListener(this);

	// ����
	mMenu->setCaption("Menu");
	mMenu->SetSize(200, 400);
	mMenu->SetPosition(300, 100);
	mMenu->Add(mContinue, 10, 10);
	mMenu->Add(mSave, 10, 50);
	mMenu->Add(mRestart, 10, 80);
	mMenu->Add(mOptions, 10, 110);
	mMenu->Add(mExit, 10, 140);
//	mMenu->addMouseListener(this);
	mMenu->SetVisible(false);

	// �������
	mRespawn->setCaption("");
	mRespawn->SetSize(400, 200);
	mRespawn->Add(mRRespawn, 16, 16);
	mRespawn->Add(mRRestart, 16, 72);
	mRespawn->Add(mRMenu, 16, 136);
	mRespawn->SetVisible(false);

	mRRespawn->setCaption("Respawn");
	mRRespawn->adjustSize();
	mRRestart->setCaption("Restart");
	mRRestart->adjustSize();
	mRMenu->setCaption("Cancel");
	mRMenu->adjustSize();


	top->Add(mWeaponIcon, 0, 536);
	top->Add(mWeaponAmmo,70, 550);
	top->Add(mAmmoLabel, 70, 580);
	top->Add(mSpellIcon, 736, 536);
	top->Add(mSpellAmmo, 710, 550);

	top->Add(mZombieLeftLabel, 600, 8);
	top->addMouseListener(this);
	top->Add(mMenu);
	
	// ��������
	mHealthBar = gcn::ProgressBarPtr(new gcn::ProgressBar());
	mHealthBar->SetSize(320, 32);
	mHealthBar->setProgress(0.7);

	// �������
	mEnergyBar = gcn::ProgressBarPtr(new gcn::ProgressBar());
	mEnergyBar->SetSize(320, 24);
	mEnergyBar->setProgress(0.7);

	top->Add(mHealthBar, 8, 8);
	top->Add(mEnergyBar, 8, 42);
	top->Add(mRespawn, 100, 100);
	top->Add(mQuestBook);

	Game::GetSingleton()->GetStory()->OnSetStage.connect(boost::bind(&Editor::OnSetStage, this, _1, _2));

	// �������������� ����� ��������
	mEntityBrush.reset(new editor::EntityBrushTool());
	mEntityBrush->SetEntityTypeID("Trash/Box");
	mEntityBrush->SetCommandManager(GetCommandManager());

	// ����� �� ��������� - ����������� ��������
	SelectEntityBrushTool();
}

void Editor::mouseClicked(gcn::MouseEvent& evt)
{
	ZombieLand* game = (ZombieLand*)(ZombieLand::GetSingleton());

	if (evt.GetSource() == mExit)
	{
		Close();
	}
	else if (evt.GetSource() == mContinue)
	{
		mMenu->SetVisible(!(mMenu->IsVisible()));
		SetPaused(mMenu->IsVisible());
	}
	else if (evt.GetSource() == mRRespawn)
	{
		mPlayer->Respawn();
		SetPaused(false);
		mRespawn->SetVisible(false);
	}
	else if (!IsPaused())
	{
		if (!(mPlayer->GetShotAction()->IsActive()))
			mPlayer->StartAction(mPlayer->GetShotAction());
	}
}

void	Editor::OnUpdate(float elapsedTime)
{
	
	char h[100];
	if (mPlayer == 0)
	{
		mPlayer = boost::shared_dynamic_cast<behaviour::Creature>(FactoryManager::GetSingleton()->GetEntity("Player")->GetBehaviour());
	}

	if (mPlayer != 0)
	{
		if (!(mPlayer->IsActive()) && !IsPaused())
		{
			//GetLevel()->GetLayer("Grass")->Add(mPlayer->GetActor());
			mRespawn->SetVisible(true);
			SetPaused(true);
		}

		float health = mPlayer->GetHealth() / mPlayer->GetMaxHealth();
		mHealthBar->setProgress(health);
		mEnergyBar->setProgress(mPlayer->GetEnergy() / mPlayer->GetMaxEnergy());

		//sprintf(h, "ZOMBIE LEFT: %d", behaviour::Zombie::GetZombieCount());
		//mZombieLeftLabel->setCaption(h);

		if (health > 0.5f)
			mHealthBar->setSelectionColor(gcn::Color(0, 255, 0));
		else if (health > 0.25f)
			mHealthBar->setSelectionColor(gcn::Color(255, 255, 0));
		else
			mHealthBar->setSelectionColor(gcn::Color(255, 0, 0));

		
		inventory::ItemPtr w = mPlayer->GetInventory()->GetSlot(inventory::Item::Weapon);
		if (w != 0)
		{
			mWeaponAmmo->setCaption(boost::lexical_cast<std::string>(w->GetAmmo()));
			mWeaponIcon->setImage(w->GetIcon());
		}
		else
			mWeaponAmmo->setCaption("");

		w = mPlayer->GetInventory()->GetSlot(inventory::Item::Spell);
		if (w != 0)
		{
			mSpellIcon->SetVisible(true);
			mSpellAmmo->SetVisible(true);
			mSpellIcon->setImage(w->GetIcon());
			mSpellAmmo->setCaption(itoa(w->GetAmmo(), h, 10));
		}
		else
		{
			mSpellIcon->SetVisible(false);
			mSpellAmmo->SetVisible(false);
		}

		w = mPlayer->GetInventory()->GetSlot(inventory::Item::Ammo);
		if (w != 0)
		{
			if (!(w->IsInfinity()))
			{
				sprintf(h, "%d", w->GetAmmo());
				mAmmoLabel->setCaption(h);
			}
			else
				mAmmoLabel->setCaption("");
		}
		else
			mAmmoLabel->setCaption("");

		if (!mPlayer->IsActive())
		{
			
		}
	}

	InputSystem* inputSystem = Engine::GetSingleton()->GetInputSystem();
	lua_State* state = Engine::GetSingleton()->GetLua();

	if (inputSystem->IsKeyUp(HGEK_Z) && inputSystem->GetKeyState(HGEK_CTRL))
	{
		if (GetCommandManager()->IsUndoPossible())
		{
			GetCommandManager()->Undo();
		}
	}
	if (inputSystem->IsKeyUp(HGEK_Y) && inputSystem->GetKeyState(HGEK_CTRL))
	{
		if (GetCommandManager()->IsRedoPossible())
		{
			GetCommandManager()->Redo();
		}
	}
	if (inputSystem->IsKeyUp(HGEK_S) && inputSystem->GetKeyState(HGEK_CTRL))
	{
		serialisation::StaticLevelSerialiser serialiser;
		serialiser.Serialise(GetLevel(), "../Data/Test/Level.xml");
	}

	if (inputSystem->IsKeyUp(HGEK_ADD))
	{
		mPlayer->GetActor()->Scale(2.1f);
	}

	if (Engine::GetSingleton()->GetInputSystem()->IsKeyDown(HGEK_ESCAPE))
	{
		mMenu->SetVisible(!(mMenu->IsVisible()));
		
		mQuestBook->UpdateQuests(Game::GetSingleton()->GetStory());
		SetPaused(mMenu->IsVisible());
	}

	if (inputSystem->IsKeyDown(HGEK_TAB))
	{
		//mMenu->setVisible(!(mMenu->isVisible()));
		
		mQuestBook->UpdateQuests(Game::GetSingleton()->GetStory());
		mQuestBook->SetVisible(!(mQuestBook->IsVisible()));
		SetPaused(mQuestBook->IsVisible());
	}

	if (inputSystem->IsKeyDown(HGEK_0))
	{
		luaL_dostring(Engine::GetSingleton()->GetLua(), "Player:GetHealth()");
	}
	if (inputSystem->IsKeyDown(HGEK_9))
	{
		ZombieLand::GetSingleton()->GetStory()->GetQuest("Level1")->SetStage(10);
	}
	
	// ��������
	if ((inputSystem->GetPadState(0, gamepad::GamepadX) || inputSystem->GetKeyState(HGEK_J)) && !mPlayer->GetShotAction()->IsActive())
	{
		mPlayer->StartAction(mPlayer->GetShotAction());
	}

	// �����������
	if ((inputSystem->GetKeyState(HGEK_R) || inputSystem->GetPadState(0, gamepad::LeftShoulder)) && !isReloading)
	{
		isReloading = true;
		if (!(mPlayer->GetReloadAction()->IsActive()))
			mPlayer->StartAction(mPlayer->GetReloadAction());
	}
	else if (!(inputSystem->GetKeyState(HGEK_R) || inputSystem->GetPadState(0, gamepad::LeftShoulder)))
	{
		isReloading = false;
	}
	
	/// ����� ������
	int leftTrigger = inputSystem->GetLeftTrigger(0);
	if ((inputSystem->IsKeyDown(HGEK_Q) || leftTrigger > 180) && !isChangingWeapon)
	{
		mPlayer->NextWeapon();
		isChangingWeapon = true;

		inventory::ItemPtr w = mPlayer->GetInventory()->GetSlot(inventory::Item::Weapon);
		if (w != 0)
			mWeaponIcon->setImage(w->GetIcon());
			
	}
	else	if (!(inputSystem->IsKeyDown(HGEK_Q) || leftTrigger > 180))
	{
		isChangingWeapon = false;
	}

	// ����������
	if ((inputSystem->GetPadState(0, gamepad::GamepadB) || inputSystem->GetKeyState(HGEK_L)) && ! mPlayer->GetSpellAction()->IsActive() && !isSpellCasting)
	{
		mPlayer->StartAction(mPlayer->GetSpellAction());
		isSpellCasting = true;
	}
	else if (!(inputSystem->GetPadState(0, gamepad::GamepadB) || inputSystem->GetKeyState(HGEK_L)))
	{
		isSpellCasting = false;
	}
	Game::GetSingleton()->GetStory()->Update(elapsedTime);

	// ����� �����������
	int rightTrigger = inputSystem->GetRightTrigger(0);
	if ((inputSystem->IsKeyDown(HGEK_E) || rightTrigger > 180) && !isChangingSpell)
	{
		mPlayer->NextSpell();
		isChangingSpell = true;			
	}
	else	if (!(inputSystem->IsKeyDown(HGEK_E) || rightTrigger > 180))
	{
		isChangingSpell = false;
	}
}

void Editor::OnStart()
{
	Game::GetSingleton()->GetStory()->Load("../Data/Quests/Story1.xml");
	SetLevel(FactoryManager::GetSingleton()->GetLevel("Level1"));
	//Engine::GetSingleton()->GetLua()->DoFile("../Data/Scripts/Triggers.lua");

	EntityPtr player = FactoryManager::GetSingleton()->GetEntity("Player");
	luabind::globals(Engine::GetSingleton()->GetLua())["Player"] = boost::shared_dynamic_cast<behaviour::Creature>(player->GetBehaviour());
	boost::shared_dynamic_cast<behaviour::Creature>(player->GetBehaviour())->SavePoint();

	mMenu->SetVisible(false);
	SetPaused(false);
}

void Editor::mousePressed(gcn::MouseEvent& mouseEvent)
{
	mCurrentTool->OnMouseDown(GetLevel()->GetLayer("Grass"), mouseEvent.getX(), mouseEvent.getY(), mouseEvent.GetButton());
}
   
void Editor::mouseReleased(gcn::MouseEvent& mouseEvent)
{
	mCurrentTool->OnMouseUp(GetLevel()->GetLayer("Grass"), mouseEvent.getX(), mouseEvent.getY(), mouseEvent.GetButton());
}

void Editor::SelectEntityBrushTool()
{
	mCurrentTool = mEntityBrush;
}

editor::CommandManagerPtr Editor::GetCommandManager()
{
	return mCommandManager;
}
};