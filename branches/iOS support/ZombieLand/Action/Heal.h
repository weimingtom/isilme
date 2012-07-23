#ifndef ZOMBIELAND_ACTION_HEAL_H
#define ZOMBIELAND_ACTION_HEAL_H

#include "../Behaviour/Creature.h"
#include <Engine/AI/AIPackage.h>
#include "Engine/AI/AIPackageDef.h"

namespace action
{
	class Heal : public Action
	{
	public: 
		Heal();
		virtual ~Heal();

		virtual void OnUpdate(float elapsedTime);

		virtual void OnStart();

		float	GetSpeed();

		void	SetSpeed(float HPPerSecond);

		float	GetCost();

		void	SetCost(float energy);
	private:
		float mSpeed;
		float mCost;
	};

	class HealPackage : public AIPackage
	{
	public:
		HealPackage();
		virtual ~HealPackage();

		virtual bool IsApplicable(BehaviourPtr behaviour) const override;

		virtual ActionPtr CreateAction() const override;
	private:
		mutable behaviour::CreaturePtr actor;
	};

	class HealPackageDef : public AIPackageDef
	{
	public:
		HealPackageDef();
		virtual ~HealPackageDef();

		virtual void Parse(TiXmlElement* element) override;
		virtual AIPackagePtr CreatePackage() override;
	};
};

#endif