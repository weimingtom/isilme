#include "ZombieLand.h"
#include "Destroyable.h"
#include "../LootTable.h"

namespace behaviour
{
	DestroyableDef::DestroyableDef()
	{
		MaxHealth = 100.0f;
		Health = MaxHealth;
		Blood = "";
		Resistance = 0.0f;
	}

	void	DestroyableDef::Parse(TiXmlElement* element)
	{
		if (element == 0)
			return;

		/// Загружаем базовые характеристики
		element->QueryFloatAttribute("Health", &Health);
		element->QueryFloatAttribute("MaxHealth", &MaxHealth);
		element->QueryFloatAttribute("Resistance", &Resistance);

		///
		char* blood = const_cast<char*>(element->Attribute("Blood"));
		Blood = blood ? blood : "";
	}

	Destroyable::Destroyable()
	{

	}

	Destroyable::~Destroyable()
	{
	}

	float	Destroyable::GetHealth() const
	{
		return mHealth;
	}

	float	Destroyable::GetMaxHealth() const
	{
		return mMaxHealth;
	}

	float	Destroyable::GetResistance() const
	{
		return mResistance;
	}

	void	Destroyable::SetHealth(float health)
	{
		mHealth = std::min(health, mMaxHealth);
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

		OnGotDamage(damage);

		if (mHealth <= 0.0f)
			OnDie();
	}

	void	Destroyable::SetHitSound(std::string sound)
	{
		mHitSound = Engine::GetSingleton()->GetResourceManager()->GetEffect(sound);
	}

	void	Destroyable::SetBloodEntity(std::string blood)
	{
		mBlood = blood;
	}

	void Destroyable::Init( DestroyableDef* def )
	{
		mHitSound = 0;
		mMaxHealth = def->MaxHealth;
		mHealth = def->Health;
		mResistance = def->Resistance;
		mBlood = def->Blood;
	}

	void Destroyable::OnGotDamage( const float damage )
	{

	}

};