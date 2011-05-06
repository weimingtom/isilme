#ifndef ZOMBIELAND_ACTION_SHOT_H
#define ZOMBIELAND_ACTION_SHOT_H

#include <Isilme.h>
#include <Engine/Action/SpecialAction.h>
#include "ZombieLand/Include/Definitions.h"

namespace action
{
	class Shot : public SpecialAction<behaviour::Creature>
	{
	public:
		Shot();
		virtual ~Shot();

		virtual void OnStart();

		void	SetSound(std::string sound);
	private:
		HEFFECT	mSound;
	};
};

#endif