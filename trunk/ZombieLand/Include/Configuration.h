#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H

#include <hge.h>
#include <string>
#include "Definitions.h"

class Configuration
{
public:
	enum Resolution
	{
		R640x480 = 0,
		R800x600 = 1,
		R1024x768 = 2,
		R1280x1024 = 3
	};

	Resolution	resolution;
	bool		fullScreen;
	bool		textureFiltering;
	float		totalVolume;
	float		musicVolume;
	float		effectsVolume;

	int			keyMoveLeft;
	int			keyMoveRight;
	int			keyMoveUp;
	int			keyMoveDown;
	int			keyFire;
	int			keyAbility;
	int			keyAmmo1;
	int			keyAmmo2;
	int			keyAmmo3;
	int			keyAmmo4;
	int			keyAbility1;
	int			keyAbility2;
	int			keyAbility3;
	int			keyAbility4;
	int			keyJump;

	Configuration(HGE* hge);

	void	Load();

	void	Save();

	void	RestoreDefaults();

	~Configuration();
protected:
	HGE*		mHGE;
	std::string	mFileName;
};

#endif