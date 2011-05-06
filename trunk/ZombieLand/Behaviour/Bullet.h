#ifndef ZOMBIELAND_BEHAVIOUR_BULLET_H
#define ZOMBIELAND_BEHAVIOUR_BULLET_H

#include <Isilme.h>
#include "Definitions.h"

namespace behaviour
{

	class BulletDef : public BehaviourDefinition
	{
		virtual BehaviourPtr Create();
	};

	class Bullet : public Behaviour
	{
	public:
		Bullet(BulletDef*);
		virtual ~Bullet();
		
		virtual void	Think(float elapsedTime);
		virtual void	HandleContact(b2Contact* contact, const b2Manifold* oldMainfold, Entity* other);

		void	SetGunslinger(BehaviourPtr behaviour);
	private:
		float mSpeed;
		float mDamage;
		BehaviourPtr	mGunslinger;
		DestroyablePtr	mTarget;
		bool	isHit;
	};

};

#endif