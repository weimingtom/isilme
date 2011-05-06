#include "ZombieLand.h"
#include "Zombie.h"
#include "Destroyable.h"

namespace behaviour
{
	DestroyableDef::DestroyableDef()
	{
		MaxHealth = 100.0f;
		Health = MaxHealth;
		Blood = "";
		Resistance = 0.0f;
	}

	BehaviourPtr DestroyableDef::Create()
	{
		return BehaviourPtr(new Destroyable(this));
	}

	void	DestroyableDef::Parse(TiXmlElement* element)
	{
		if (element == 0)
			return;

		element->QueryFloatAttribute("Health", &Health);
		element->QueryFloatAttribute("MaxHealth", &MaxHealth);
		element->QueryFloatAttribute("Resistance", &Resistance);

		char* blood = const_cast<char*>(element->Attribute("Blood"));
		Blood = blood ? blood : "";
	}

	Destroyable::Destroyable(DestroyableDef* def)
	{
		mHitSound = 0;
		mMaxHealth = def->Health;
		mHealth = def->MaxHealth;
		mResistance = def->Resistance;
		mBlood = def->Blood;

		mDieAction = action::DiePtr(new action::Die());
	}

	Destroyable::~Destroyable()
	{
	}

	float	Destroyable::GetHealth()
	{
		return mHealth;
	}

	float	Destroyable::GetMaxHealth()
	{
		return mMaxHealth;
	}

	float	Destroyable::GetResistance()
	{
		return mResistance;
	}

	void	Destroyable::SetHealth(float health)
	{
		mHealth = min(health, mMaxHealth);
	}

	void	Destroyable::SetMaxHealth(float health)
	{
		mMaxHealth = health;
	}

	void	Destroyable::SetResistance(float resistance)
	{
		mResistance = resistance;
	}

	void	Destroyable::Damage(float damage)
	{
		mHealth -= damage * (1.0f - mResistance);

		if (mHitSound)
		Engine::GetSingleton()->GetSoundSystem()->PlayEffect(mHitSound);

		if (mBlood != "")
		{
			EntityPtr blood = FactoryManager::GetSingleton()->CreateEntity(mBlood, "", GetLevel());
			blood->SetPosition(GetActor()->GetPosition().x, GetActor()->GetPosition().y);
			blood->SetAngle(GetActor()->GetAngle());
			GetLevel()->GetLayer("Grass")->Add(blood);
		}
	}

	void	Destroyable::Think(float elapsedTime)
	{
		if (mHealth <= 0.0f)
		{
			if (!mDieAction->IsActive())
				StartAction(mDieAction);
		}
	}

	action::DiePtr	Destroyable::GetDieAction()
	{
		return mDieAction;
	}

	void	Destroyable::SetHitSound(std::string sound)
	{
		mHitSound = Engine::GetSingleton()->GetResourceManager()->GetEffect(sound);
	}

	void	Destroyable::SetBloodEntity(std::string blood)
	{
		mBlood = blood;
	}
};