#ifndef TUTORIALS_MYGAME_H
#define TUTORIALS_MYGAME_H

#include "Definitions.h"

class MyGame : public HGEGame
{
public:
	MyGame();
	virtual ~MyGame();

	virtual void Init() override;
};
#endif