#ifndef ZOMBIELAND_ACTION_ATTACK_H
#define ZOMBIELAND_ACTION_ATTACK_H

#include "../Definitions.h"
#include "../Behaviour/Creature.h"

namespace action
{
	class Attack : public Action
	{
	public:
		Attack();
		virtual ~Attack();

		virtual void OnStart();

		void	SetSound(std::string sound);
	private:
		HEFFECT	mSound;
		float mDamage;
		float mDistance;
		float mWidth;
	};
};

#endif