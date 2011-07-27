#include "ZombieLand.h"
#include "FactoryManager.h"
#include "Engine/Quest/Story.h"
#include <string>

#include "Play.h"
#include "ZombieLand/Behaviour/Player.h"
#include "ZombieLand/Behaviour/Zombie.h"
#include "Engine/GUI/ProgressBar.h"

namespace state
{
Play::Play() : State()
{	
	isReloading = false;
	isChangingWeapon = false;
	// Init GUI
	gcn::Container* top;
	//
	top = new gcn::Container();
    // We set the dimension of the top container to match the screen.
    top->setDimension(gcn::Rectangle(0, 0, 800, 600));
	top->setBackgroundColor(gcn::Color(0,0,0,0));
	top->setBaseColor(gcn::Color(0,0,0,0));
	top->setFocusable(true);
	gcn::ImageFont* font = new gcn::ImageFont("../Data/Fonts/fixedfont.bmp", " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
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

	mAmmo1Button	= new gcn::ImageButton("../Data/Textures/Icons/Ammo1.png");
	mAmmo2Button	= new gcn::ImageButton("../Data/Textures/Icons/Ammo2.png");
	mAmmo3Button	= new gcn::ImageButton("../Data/Textures/Icons/Ammo3.png");
	mAmmo4Button	= new gcn::ImageButton("../Data/Textures/Icons/Ammo4.png");
	
	mAbility1Button	= new gcn::ImageButton("../Data/Textures/Icons/Ability1.png");
	mAbility2Button	= new gcn::ImageButton("../Data/Textures/Icons/Ability2.png");
	mAbility3Button	= new gcn::ImageButton("../Data/Textures/Icons/Ability3.png");
	mAbility4Button	= new gcn::ImageButton("../Data/Textures/Icons/Ability4.png");

	mHealthImage	= new gcn::Icon();
	mHealthField	= new gcn::Label("none");
	mWeaponIcon		= new gcn::Icon();
	mWeaponAmmo		= new gcn::ProgressBar();

	// Иконка здоровья
	mHealthImage->setImage(gcn::Image::load("../Data/Textures/Icons/Health.png"));
	mHealthImage->setSize(64, 64);

	// Иконка оружия
	mWeaponIcon->setImage(gcn::Image::load("../Data/Icons/Empty.png"));
	mWeaponIcon->setSize(64, 64);

	// Уровень заряда
	mWeaponAmmo->setProgress(100);
	mWeaponAmmo->setSelectionColor(gcn::Color(255, 100, 100));
	mWeaponAmmo->setSize(64, 16);
	
	// Кнопка обычных патронов
	mAmmo1Button->setBackgroundColor(gcn::Color(255, 0, 0, 100));
	mAmmo1Button->setSize(64, 64);
	mAmmo1Button->setFrameSize(0);
	mAmmo1Button->setFont(font);
	mAmmo1Button->setAlignment(gcn::Graphics::CENTER);
//	mAmmo1Button->addMouseListener(this);

	// Кнопка зажигательных патронов
	mAmmo2Button->setBackgroundColor(gcn::Color(255, 0, 0, 100));
	mAmmo2Button->setSize(64, 64);

	mAmmo2Button->setFrameSize(0);
//	mAmmo2Button->addMouseListener(this);

	// Кнопка усиленных патронов
	mAmmo3Button->setBackgroundColor(gcn::Color(255, 0, 0, 100));
	mAmmo3Button->setSize(64, 64);
	mAmmo3Button->setFrameSize(0);
//	mAmmo3Button->addMouseListener(this);

	// Кнопка разрывных патронов
	mAmmo4Button->setBackgroundColor(gcn::Color(255, 0, 0, 100));
	mAmmo4Button->setSize(64, 64);
	mAmmo4Button->setFrameSize(0);
//	mAmmo4Button->addMouseListener(this);

	// Способность щит
	mAbility1Button->setBackgroundColor(gcn::Color(255, 0, 0, 100));
	mAbility1Button->setSize(64, 64);
	mAbility1Button->setFrameSize(0);
	//mAbility1Button->addMouseListener(this);

	// Знак аард
	mAbility2Button->setBackgroundColor(gcn::Color(255, 0, 0, 100));
	mAbility2Button->setSize(64, 64);
	mAbility2Button->setFrameSize(0);
	//mAbility2Button->addMouseListener(this);

	// ??
	mAbility3Button->setBackgroundColor(gcn::Color(255, 0, 0, 100));
	mAbility3Button->setSize(64, 64);
	mAbility3Button->setFrameSize(0);
	//mAbility3Button->addMouseListener(this);

	// ??
	mAbility4Button->setBackgroundColor(gcn::Color(255, 0, 0, 100));
	mAbility4Button->setSize(64, 64);
	mAbility4Button->setFrameSize(0);
//	mAbility4Button->addMouseListener(this);

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

	// 
	//top->add(mAmmo1Button, 0, 536);
	//top->add(mAmmo2Button, 64, 536);
	//top->add(mAmmo3Button, 128, 536);
	//top->add(mAmmo4Button, 192, 536);
	top->add(mAbility1Button, 554, 536);
	top->add(mAbility2Button, 618, 536);
	top->add(mAbility3Button, 682, 536);
	top->add(mWeaponIcon, 0, 520);
	top->add(mWeaponAmmo, 0, 584);
	//top->add(mAbility4Button, 746, 536);
	//top->add(mHealthImage, 400, 500);
	//top->add(mHealthField, 420, 530);

	//top->add(mOrbImage, 700, 10);
	//top->add(mOrbLabel, 732, 42);
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
}

void Play::mouseClicked(gcn::MouseEvent& evt)
{
	ZombieLand* game = (ZombieLand*)(ZombieLand::GetSingleton());

	if (evt.getSource() == mExit)
	{
		Close();
	}
	else if (evt.getSource() == mAbility3Button)
	{
		if (!(mPlayer->GetHealAction()->IsActive()) && mPlayer->GetEnergy() >= mPlayer->GetHealAction()->GetCost())
			mPlayer->StartAction(mPlayer->GetHealAction());
	}
	else if (evt.getSource() == mAbility1Button)
	{
		if (!(mPlayer->GetShildAction()->IsActive()))
			mPlayer->StartAction(mPlayer->GetShildAction());
		else
			mPlayer->GetShildAction()->Stop();
	}
	else if (evt.getSource() == mAbility2Button)
	{
		if (!(mPlayer->GetWindAction()->IsActive()) && mPlayer->GetEnergy() >= mPlayer->GetWindAction()->GetCost())
			mPlayer->StartAction(mPlayer->GetWindAction());
	}
	else if (evt.getSource() == mContinue)
	{
		mMenu->setVisible(!(mMenu->isVisible()));
		SetPaused(mMenu->isVisible());
	}
	else
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
		if (mPlayer->GetHealth() <= 0.0f)
			GetLevel()->GetLayer("Grass")->Add(mPlayer->GetActor());
		float health = mPlayer->GetHealth() / mPlayer->GetMaxHealth();
		mHealthBar->setProgress(health);
		mEnergyBar->setProgress(mPlayer->GetEnergy() / mPlayer->GetMaxEnergy());

		sprintf(h, "ZOMBIE LEFT: %d", behaviour::Zombie::GetZombieCount());
		mZombieLeftLabel->setCaption(h);

		if (health > 0.5f)
			mHealthBar->setSelectionColor(gcn::Color(0, 255, 0));
		else if (health > 0.25f)
			mHealthBar->setSelectionColor(gcn::Color(255, 255, 0));
		else
			mHealthBar->setSelectionColor(gcn::Color(255, 0, 0));

		
		ItemPtr w = mPlayer->GetInventory()->GetSlot(Item::Weapon);
		if (w != 0)
		{
			mWeaponAmmo->setProgress((float)w->GetAmmo() / w->GetMaxAmmo());
			mWeaponIcon->setImage(w->GetIcon());
		}
		else
			mWeaponAmmo->setProgress(1.0f);
	}

	InputSystem* inputSystem = Engine::GetSingleton()->GetInputSystem();

	if (Engine::GetSingleton()->GetInputSystem()->IsKeyDown(HGEK_ESCAPE))
	{
		mMenu->setVisible(!(mMenu->isVisible()));
		SetPaused(mMenu->isVisible());
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
		mPlayer->GetInventory()->GetSlot(Item::Ammo)->UseBy(mPlayer->GetActor());
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

		ItemPtr w = mPlayer->GetInventory()->GetSlot(Item::Weapon);
		if (w != 0)
			mWeaponIcon->setImage(w->GetIcon());
			
	}
	else	if (!(inputSystem->IsKeyDown(HGEK_Q) || leftTrigger > 180))
	{
		isChangingWeapon = false;
	}

	Game::GetSingleton()->GetStory()->Update(elapsedTime);
}

void Play::OnStart()
{
	GetLevel()->Load("../Data/Levels/Level1.xml");
	//Engine::GetSingleton()->GetLua()->DoFile("../Data/Scripts/Triggers.lua");

	EntityPtr player = FactoryManager::GetSingleton()->GetEntity("Player");

	mMenu->setVisible(false);
	SetPaused(false);
}
};