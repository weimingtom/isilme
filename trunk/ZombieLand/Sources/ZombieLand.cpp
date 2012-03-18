#include "ZombieLand.h"
#include "ZombieLand/State/Play.h"
#include "ZombieLand/Graphics/Creature.h"
#include "ZombieLand/Behaviour/Creature.h"
#include "ZombieLand/Behaviour/Bullet.h"
#include "ZombieLand/Behaviour/Item.h"
#include "ZombieLand/Behaviour/Door.h"

#include "ZombieLand/Items/Weapon.h"
#include "ZombieLand/Items/Ammo.h"
#include "ZombieLand/Items/Spell.h"
#include "ZombieLand/LootTable.h"
#include <Engine/AI/Factories/AIPackageFactory.h>
#include <ZombieLand/WanderPackage.h>
#include <ZombieLand/Action/AgressionPackage.h>
#include <ZombieLand/Action/ControlPackage.h>
#include <ZombieLand/Action/AvoidPackage.h>
#include "Definitions.h"
#include "Engine/Story/Story.h"

ZombieLand* ZombieLand::GetSingleton()
{
	return (ZombieLand*)Game::GetSingleton();
}
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

	// Регистрируем поведение
	factoryManager->RegisterBehaviour("Creature", BehaviourFactory<behaviour::CreatureDef>::New());
//	factoryManager->RegisterBehaviour("Destroyable", BehaviourFactory<behaviour::DestroyableDef>::New());
	factoryManager->RegisterBehaviour("Bullet", BehaviourFactory<behaviour::BulletDef>::New());
	factoryManager->RegisterBehaviour("Door", BehaviourFactory<behaviour::DoorDef>::New());
	factoryManager->RegisterBehaviour("Item", BehaviourFactory<behaviour::ItemDef>::New());

	// Регистрируем камеру
	factoryManager->RegisterCamera("Following", new CameraFactory<camera::FollowingCameraDef>());

	// Регистрируем предметы
	factoryManager->RegisterItem("Weapon", inventory::ItemFactory<inventory::WeaponDef>::New());
	factoryManager->RegisterItem("Ammo", inventory::ItemFactory<inventory::AmmoDef>::New());
	factoryManager->RegisterItem("Spell", inventory::ItemFactory<inventory::SpellDef>::New());

	// Регистрируем пакеты ИИ
	factoryManager->GetAIPalette()->RegisterAIType("Wander", AIPackageFactory<WanderPackageDef>::New());
	factoryManager->GetAIPalette()->RegisterAIType("Control", AIPackageFactory<ControlPackageDef>::New());
	factoryManager->GetAIPalette()->RegisterAIType("Agression", AIPackageFactory<AgressionPackageDef>::New());
	factoryManager->GetAIPalette()->RegisterAIType("Avoid", AIPackageFactory<AvoidPackageDef>::New());
	
	FactoryManager::GetSingleton()->LoadMasterFile("../Data/Master.imf");
//	factoryManager->LoadConversations("../Data/Conversations.xml");
//	factoryManager->LoadDataFile("../Data/Master.xml");
//	factoryManager->LoadItems("../Data/Items.xml");
	LootManager::GetSingleton()->Load("../Data/Loot.xml");
	//FactoryManager::GetSingleton()->LoadEntities("../Data/Entities.xml");

	playState.reset(new state::Play());
	Game::GetSingleton()->GetStory()->Load("../Data/Quests/Story1.xml");
	//StatePtr editorState = StatePtr(new state::Editor());
	//FactoryManager::GetSingleton()->LoadLevel("../Data/Levels/Level1.xml");
	//FactoryManager::GetSingleton()->LoadLevel("../Data/Levels/Level2.xml");

	GetStateManager()->Push(playState);
	//GetStateManager()->Push(editorState);

	luaL_dofile(Engine::GetSingleton()->GetLua(), "../Data/Scripts/script.lua");
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