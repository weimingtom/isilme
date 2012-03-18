#include "ZombieLand.h"
#include "Configuration.h"

Configuration::Configuration(HGE* hge) :
	mHGE(hge)
{
	RestoreDefaults();
}

Configuration::~Configuration()
{
}

void Configuration::Load()
{
	RestoreDefaults();

	// Загрузка общих параметров

	// Загрузка видео-параметров
	std::string res = mHGE->Ini_GetString("VIDEO", "Resolution",  "800x600");
	if (res == "640x480")
		resolution = Configuration::R640x480;
	else if (res == "800x600")
		resolution = Configuration::R800x600;
	else if (res == "1024x768")
		resolution = Configuration::R1024x768;
	else if (res == "1280x1024")
		resolution = Configuration::R1280x1024;

	textureFiltering = mHGE->Ini_GetInt("VIDEO", "TextureFiltering", textureFiltering);
	fullScreen		= mHGE->Ini_GetInt("VIDEO", "FullScreen", fullScreen);
	
	// Загрузка аудио-параметров
	totalVolume = mHGE->Ini_GetFloat("SOUND", "TotalVolume", totalVolume);
	musicVolume = mHGE->Ini_GetFloat("SOUND", "MusicVolume", musicVolume);
	effectsVolume = mHGE->Ini_GetFloat("SOUND", "EffectsVolume", effectsVolume);

	// Загрузка конфигурации управления
	keyMoveLeft		= mHGE->Ini_GetInt("CONTROL", "MoveLeft",	keyMoveLeft);
	keyMoveRight	= mHGE->Ini_GetInt("CONTROL", "MoveRight",	keyMoveRight);
	keyMoveUp		= mHGE->Ini_GetInt("CONTROL", "MoveUp",		keyMoveUp);
	keyMoveDown		= mHGE->Ini_GetInt("CONTROL", "MoeDown",	keyMoveDown);
	keyFire			= mHGE->Ini_GetInt("CONTROL", "Fire",		keyFire);
	keyJump			= mHGE->Ini_GetInt("CONTROL", "Jump",		keyJump);
	keyAmmo1		= mHGE->Ini_GetInt("CONTROL", "Ammo1",		keyAmmo1);
	keyAmmo2		= mHGE->Ini_GetInt("CONTROL", "Ammo2",		keyAmmo2);
	keyAmmo3		= mHGE->Ini_GetInt("CONTROL", "Ammo3",		keyAmmo3);
	keyAmmo4		= mHGE->Ini_GetInt("CONTROL", "Ammo4",		keyAmmo4);
	keyAbility		= mHGE->Ini_GetInt("CONTROL", "Ability",	keyAbility);
	keyAbility1		= mHGE->Ini_GetInt("CONTROL", "Ability1",	keyAbility1);
	keyAbility2		= mHGE->Ini_GetInt("CONTROL", "Ability2",	keyAbility2);
	keyAbility3		= mHGE->Ini_GetInt("CONTROL", "Ability3",	keyAbility3);
	keyAbility4		= mHGE->Ini_GetInt("CONTROL", "Ability4",	keyAbility4);

}

void Configuration::Save()
{
	// Сохранение общих параметров

	// Загрузка видео-параметров
	std::string res = "640x480";
	if (resolution == Configuration::R800x600)
		res = "800x600";
	else if (resolution == Configuration::R1024x768)
		res = "1024x768";
	else 
		res = "1280x1024";

	mHGE->Ini_SetString("VIDEO", "Resolution", res.c_str());
	mHGE->Ini_SetInt("VIDEO", "TextureFiltering", textureFiltering);
	mHGE->Ini_SetInt("VIDEO", "FullScreen", fullScreen);

	// Сохранение аудио-параметров
	mHGE->Ini_SetFloat("SOUND", "TotalVolume", totalVolume);
	mHGE->Ini_SetFloat("SOUND", "MusicVolume", musicVolume);
	mHGE->Ini_SetFloat("SOUND", "EffectsVolume", effectsVolume);

	// Сохранение конфигурации управления
	mHGE->Ini_SetInt("CONTROL", "MoveLeft",	keyMoveLeft);
	mHGE->Ini_SetInt("CONTROL", "MoveRight",keyMoveRight);
	mHGE->Ini_SetInt("CONTROL", "MoveUp",	keyMoveUp);
	mHGE->Ini_SetInt("CONTROL", "MoeDown",	keyMoveDown);
	mHGE->Ini_SetInt("CONTROL", "Fire",		keyFire);
	mHGE->Ini_SetInt("CONTROL", "Jump",		keyJump);
	mHGE->Ini_SetInt("CONTROL", "Ammo1",	keyAmmo1);
	mHGE->Ini_SetInt("CONTROL", "Ammo2",	keyAmmo2);
	mHGE->Ini_SetInt("CONTROL", "Ammo3",	keyAmmo3);
	mHGE->Ini_SetInt("CONTROL", "Ammo4",	keyAmmo4);
	mHGE->Ini_SetInt("CONTROL", "Ability",	keyAbility);
	mHGE->Ini_SetInt("CONTROL", "Ability1",	keyAbility1);
	mHGE->Ini_SetInt("CONTROL", "Ability2",	keyAbility2);
	mHGE->Ini_SetInt("CONTROL", "Ability3",	keyAbility3);
	mHGE->Ini_SetInt("CONTROL", "Ability4",	keyAbility4);
}

void Configuration::RestoreDefaults()
{
	// Загрузка видео-параметров
	resolution = Configuration::R800x600;
	textureFiltering = true;
	fullScreen = false;

	// Загрузка аудио-параметров
	totalVolume = 50.0f;
	musicVolume = 50.0f;
	effectsVolume = 50.0f;

	// Загрузка конфигурации управления
	keyMoveLeft		= HGEK_A;
	keyMoveRight	= HGEK_D;
	keyMoveUp		= HGEK_W;
	keyMoveDown		= HGEK_S;
	keyFire			= HGEK_LBUTTON;
	keyJump			= HGEK_SPACE;
	keyAmmo1		= HGEK_1;
	keyAmmo2		= HGEK_2;
	keyAmmo3		= HGEK_3;
	keyAmmo4		= HGEK_4;
	keyAbility		= HGEK_RBUTTON;
	keyAbility1		= HGEK_5;
	keyAbility2		= HGEK_6;
	keyAbility3		= HGEK_7;
	keyAbility4		= HGEK_8;
}