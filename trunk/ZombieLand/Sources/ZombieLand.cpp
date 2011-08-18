#include "ZombieLand.h"
#include "ZombieLand/State/Play.h"
#include "ZombieLand/Graphics/Creature.h"
#include "ZombieLand/Graphics/Player.h"
#include "ZombieLand/Behaviour/Creature.h"
#include "ZombieLand/Behaviour/Player.h"
#include "ZombieLand/Behaviour/Bullet.h"
#include "ZombieLand/Behaviour/Zombie.h"
#include "ZombieLand/Behaviour/Item.h"

#include "ZombieLand/Items/Weapon.h"
#include "ZombieLand/Items/Ammo.h"
#include "ZombieLand/Items/Spell.h"

ZombieLand::ZombieLand()
{

	mConfiguration = new Configuration(mHGE);
	mConfiguration->Load();

}

ZombieLand::~ZombieLand()
{
	mConfiguration->Save();
	delete mConfiguration;
}

Configuration*	ZombieLand::GetConfguration()
{
	return mConfiguration;
}

void	ZombieLand::Init()
{
	ScriptAPI::RegisterAPI();

	mConfiguration->Load();
	
	FactoryPtr factoryManager = FactoryManager::GetSingleton();

	// Регистрируем графику
	factoryManager->RegisterGraphics("Creature", GraphicsFactory<graphics::CreatureDef>::New());
	factoryManager->RegisterGraphics("Player", GraphicsFactory<graphics::PlayerDef>::New());

	// Регистрируем поведение
	factoryManager->RegisterBehaviour("Player", new BehaviourFactory<behaviour::PlayerDef>());
	factoryManager->RegisterBehaviour("Zombie", new BehaviourFactory<behaviour::ZombieDef>());
	factoryManager->RegisterBehaviour("Destroyable", new BehaviourFactory<behaviour::DestroyableDef>());
	factoryManager->RegisterBehaviour("Bullet", new BehaviourFactory<behaviour::BulletDef>());
	factoryManager->RegisterBehaviour("Item", new BehaviourFactory<behaviour::ItemDef>());

	// Регистрируем камеру
	factoryManager->RegisterCamera("Following", new CameraFactory<camera::FollowingCameraDef>());

	// Регистрируем предметы
	factoryManager->RegisterItem("Weapon", inventory::ItemFactory<inventory::WeaponDef>::New());
	factoryManager->RegisterItem("Ammo", inventory::ItemFactory<inventory::AmmoDef>::New());

	factoryManager->LoadItems("../Data/Items.xml");
	playState = StatePtr(new state::Play());

	GetStateManager()->Push(playState);

	Engine::GetSingleton()->GetLua()->DoFile("../Data/Scripts/script.lua");
}

void	ZombieLand::ApplyConfiguration()
{
	// Видео-опции
	int width;
	int height;
	if (mConfiguration->resolution == Configuration::R640x480)
	{
		width = 640;
		height = 480;
	}
	else if  (mConfiguration->resolution == Configuration::R800x600)
	{
		width = 800;
		height = 600;
	}
	else if (mConfiguration->resolution == Configuration::R1024x768)
	{
		width = 1024;
		height = 768;
	}
	else if (mConfiguration->resolution == Configuration::R1280x1024)
	{
		width = 1280;
		height = 1024;
	}

	mHGE->System_SetState(HGE_WINDOWED, !(mConfiguration->fullScreen)); 
	mHGE->System_SetState(HGE_TEXTUREFILTER, mConfiguration->textureFiltering);
	mHGE->System_SetState(HGE_SCREENWIDTH, width);
	mHGE->System_SetState(HGE_SCREENHEIGHT, height);

	// Аудио-опции

	// Настройки упправления
}