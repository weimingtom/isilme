#include "ZombieLand.h"
#include "FactoryManager.h"
#include "Engine/Quest/Story.h"
#include "Engine/Quest/Quest.h"
#include "Engine/Quest/Stage.h"
#include <string>
#include <guichan.hpp>
#include "Play.h"
#include "ZombieLand/Behaviour/Player.h"
#include "ZombieLand/Behaviour/Zombie.h"
#include "Engine/GUI/ProgressBar.h"
#include "Engine/GUI/QuestBook.h"
#include <luabind/function.hpp>
#include "Engine/Quest/Quest.h"
#include "Engine/Quest/Stage.h"

namespace state
{

	void	Play::OnSetStage(story::QuestPtr quest, int stage)
	{
		mZombieLeftLabel->setCaption(quest->GetStage(stage)->GetText());
	}

Play::Play() : State()
{	
	isReloading = false;
	isChangingWeapon = false;
	isChangingSpell = false;
	isSpellCasting = false;
	// Init GUI
	//
	top = new gcn::Container();
    // We set the dimension of the top container to match the screen.
    top->setDimension(gcn::Rectangle(0, 0, 800, 600));
	top->setBackgroundColor(gcn::Color(0,0,0,0));
	top->setBaseColor(gcn::Color(0,0,0,0));
	top->setFocusable(true);
	gcn::Font* font = new gcn::HGEImageFont("../Data/Fonts/font1.fnt");//new gcn::ImageFont("../Data/Fonts/fixedfont.bmp", " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
	gcn::Widget::setGlobalFont(font);
    // Finally we pass the top widget to the Gui object.
    GetGUI()->setTop(top);
	
	// Элементы
	mMenu		= new gcn::Window();
	mContinue	= new gcn::Button();
	mSave		= new gcn::Button();
	mRestart	= new gcn::Button();
	mOptions	= new gcn::Button();
	mExit		= new gcn::Button();

	mRespawn	= new gcn::Window();
	mRRestart	= new gcn::Button();
	mRRespawn	= new gcn::Button();
	mRMenu		= new gcn::Button();

	mHealthImage	= new gcn::Icon();
	mHealthField	= new gcn::Label("none");
	mAmmoLabel		= new gcn::HGELabel("../Data/Fonts/font1.fnt");
	mWeaponIcon		= new gcn::Icon();
	mWeaponAmmo		= new gcn::HGELabel("../Data/Fonts/font1.fnt");
	mSpellIcon		= new gcn::Icon();
	mSpellAmmo		= new gcn::HGELabel("../Data/Fonts/font1.fnt");

	mQuestBook		= new gcn::QuestBook();

	mQuestBook->setVisible(false);

	// Иконка способности
	mSpellIcon->setSize(64, 64);
	mSpellIcon->setImage(gcn::Image::load("../Data/Icons/Empty.png"));

	// Иконка здоровья
	mHealthImage->setImage(gcn::Image::load("../Data/Textures/Icons/Health.png"));
	mHealthImage->setSize(64, 64);

	// Иконка оружия
	mWeaponIcon->setImage(gcn::Image::load("../Data/Icons/Empty.png"));
	mWeaponIcon->setSize(64, 64);

	// Уровень заряда
	mWeaponAmmo->setTextColor(gcn::Color(255,255,255));

	// Количество заклинаний
	mSpellAmmo->setTextColor(gcn::Color(255,255,255));

	// Количество паторнов
	mAmmoLabel->setTextColor(gcn::Color(255, 255, 255));
	
	// Иконка бонусов
	mOrbImage = new gcn::Icon("../Data/Textures/Icons/Orb.png");
	mOrbImage->setSize(64, 64);

	// Количество бонусов
	mOrbLabel = new gcn::Label("x");

	// Количество зомби
	mZombieLeftLabel = new gcn::HGELabel("../Data/Fonts/font1.fnt");
	mZombieLeftLabel->setTextColor(gcn::Color(200, 200, 200));
	//mZombieLeftLabel->setForegroundColor(gcn::Color(200, 200, 200));

	// Продолжить игру
	mContinue->setCaption("Continue");
	mContinue->setSize(150, 20);
//	mContinue->addMouseListener(this);

	// Сохранить игру
	mSave->setCaption("Save");
	mSave->setSize(150, 20);
//	mSave->addMouseListener(this);

	// Опции
	mOptions->setCaption("Options");
	mOptions->setSize(150, 20);
//	mOptions->addMouseListener(this);

	// Завершить уровень
	mExit->setCaption("Exit to menu");
	mExit->setSize(150, 20);
//	mExit->addMouseListener(this);

	// Начать сначала
	mRestart->setCaption("Restart");
	mRestart->setSize(150, 20);
//	mRestart->addMouseListener(this);

	// Меню
	mMenu->setCaption("Menu");
	mMenu->setSize(200, 400);
	mMenu->setPosition(300, 100);
	mMenu->add(mContinue, 10, 10);
	mMenu->add(mSave, 10, 50);
	mMenu->add(mRestart, 10, 80);
	mMenu->add(mOptions, 10, 110);
	mMenu->add(mExit, 10, 140);
//	mMenu->addMouseListener(this);
	mMenu->setVisible(false);

	// Респаун
	mRespawn->setCaption("");
	mRespawn->setSize(400, 200);
	mRespawn->add(mRRespawn, 16, 16);
	mRespawn->add(mRRestart, 16, 72);
	mRespawn->add(mRMenu, 16, 136);
	mRespawn->setVisible(false);

	mRRespawn->setCaption("Respawn");
	mRRespawn->adjustSize();
	mRRestart->setCaption("Restart");
	mRRestart->adjustSize();
	mRMenu->setCaption("Cancel");
	mRMenu->adjustSize();


	top->add(mWeaponIcon, 0, 536);
	top->add(mWeaponAmmo,70, 550);
	top->add(mAmmoLabel, 70, 580);
	top->add(mSpellIcon, 736, 536);
	top->add(mSpellAmmo, 710, 550);

	top->add(mZombieLeftLabel, 600, 8);
	top->addMouseListener(this);
	top->add(mMenu);
	
	// Здоровье
	mHealthBar = new gcn::ProgressBar();
	mHealthBar->setSize(320, 32);
	mHealthBar->setProgress(0.7);

	// Энергия
	mEnergyBar = new gcn::ProgressBar();
	mEnergyBar->setSize(320, 24);
	mEnergyBar->setProgress(0.7);

	top->add(mHealthBar, 8, 8);
	top->add(mEnergyBar, 8, 42);
	top->add(mRespawn, 100, 100);
	top->add(mQuestBook);

	Game::GetSingleton()->GetStory()->OnSetStage.connect(boost::bind(&Play::OnSetStage, this, _1, _2));
}

void Play::mouseClicked(gcn::MouseEvent& evt)
{
	ZombieLand* game = (ZombieLand*)(ZombieLand::GetSingleton());

	if (evt.getSource() == mExit)
	{
		Close();
	}
	else if (evt.getSource() == mContinue)
	{
		mMenu->setVisible(!(mMenu->isVisible()));
		SetPaused(mMenu->isVisible());
	}
	else if (evt.getSource() == mRRespawn)
	{
		mPlayer->Respawn();
		SetPaused(false);
		mRespawn->setVisible(false);
	}
	else if (!IsPaused())
	{
		if (!(mPlayer->GetShotAction()->IsActive()))
			mPlayer->StartAction(mPlayer->GetShotAction());
	}
}

void	Play::OnUpdate(float elapsedTime)
{

	char h[100];
	if (mPlayer == 0)
	{
		mPlayer = boost::shared_dynamic_cast<behaviour::Player>(FactoryManager::GetSingleton()->GetEntity("Player")->GetBehaviour());
	}

	if (mPlayer != 0)
	{
		if (!(mPlayer->IsActive()) && !IsPaused())
		{
			//GetLevel()->GetLayer("Grass")->Add(mPlayer->GetActor());
			mRespawn->setVisible(true);
			SetPaused(true);
		}

		float health = mPlayer->GetHealth() / mPlayer->GetMaxHealth();
		mHealthBar->setProgress(health);
		mEnergyBar->setProgress(mPlayer->GetEnergy() / mPlayer->GetMaxEnergy());

		sprintf(h, "ZOMBIE LEFT: %d", behaviour::Zombie::GetZombieCount());
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
			mSpellIcon->setVisible(true);
			mSpellAmmo->setVisible(true);
			mSpellIcon->setImage(w->GetIcon());
			mSpellAmmo->setCaption(itoa(w->GetAmmo(), h, 10));
		}
		else
		{
			mSpellIcon->setVisible(false);
			mSpellAmmo->setVisible(false);
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
	lua_State* state = Engine::GetSingleton()->GetLua()->GetState();

	if (inputSystem->IsKeyDown(HGEK_Y))
	{
		if (luaL_loadstring(state, "return function(stage) local q = Story:GetQuest(\"Level1\");	q:SetStage(stage); end") == 0)
		{
			luabind::object f = luabind::object(luabind::from_stack(state, lua_gettop(state)));
			luabind::object t = f();
			t(20);
		}
	}
	if (Engine::GetSingleton()->GetInputSystem()->IsKeyDown(HGEK_ESCAPE))
	{
		mMenu->setVisible(!(mMenu->isVisible()));
		
		mQuestBook->UpdateQuests(Game::GetSingleton()->GetStory());
		SetPaused(mMenu->isVisible());
	}

	if (inputSystem->IsKeyDown(HGEK_TAB))
	{
		//mMenu->setVisible(!(mMenu->isVisible()));
		
		mQuestBook->UpdateQuests(Game::GetSingleton()->GetStory());
		mQuestBook->setVisible(!(mQuestBook->isVisible()));
		SetPaused(mQuestBook->isVisible());
	}

	if (inputSystem->IsKeyDown(HGEK_0))
	{
		luaL_dostring(Engine::GetSingleton()->GetLua()->GetState(), "Player:GetHealth()");
	}
	if (inputSystem->IsKeyDown(HGEK_9))
	{
		ZombieLand::GetSingleton()->GetStory()->GetQuest("Level1")->SetStage(10);
	}
	
	// Стрельба
	if ((inputSystem->GetPadState(0, gamepad::GamepadX) || inputSystem->GetKeyState(HGEK_J)) && !mPlayer->GetShotAction()->IsActive())
	{
		mPlayer->StartAction(mPlayer->GetShotAction());
	}

	// Перезарядка
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
	
	/// Смена оружия
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

	// Заклинание
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

	// Смена способности
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

void Play::OnStart()
{
	Game::GetSingleton()->GetStory()->Load("../Data/Quests/Story1.xml");
	GetLevel()->Load("../Data/Levels/Level1.xml");
	//Engine::GetSingleton()->GetLua()->DoFile("../Data/Scripts/Triggers.lua");

	EntityPtr player = FactoryManager::GetSingleton()->GetEntity("Player");
	luabind::globals(Engine::GetSingleton()->GetLua()->GetState())["Player"] = boost::shared_dynamic_cast<behaviour::Creature>(player->GetBehaviour());
	boost::shared_dynamic_cast<behaviour::Player>(player->GetBehaviour())->SavePoint();

	mMenu->setVisible(false);
	SetPaused(false);
}
};