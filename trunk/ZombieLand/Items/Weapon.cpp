#include "ZombieLand.h"
#include "Weapon.h"
#include "ZombieLand/Behaviour/Bullet.h"

namespace items
{
	Weapon::Weapon()
	{
		SetSlot(Item::Weapon);
		mMaxAmmo = 10;
		mAmmo = 10;
		isInfinity = false;
	}

	Weapon::~Weapon()
	{
	}

	void	Weapon::OnUse(EntityPtr actor)
	{
		if (!isInfinity)
		{
			if (mAmmo <= 0)
				return;
			mAmmo--;
		}

		if (GetUseSound())
			Engine::GetSingleton()->GetSoundSystem()->PlayEffect(GetUseSound());

		EntityPtr bullet = FactoryManager::GetSingleton()->CreateEntity("Bullet", "", actor->GetLevel());
		bullet->SetAngle(actor->GetAngle());
		bullet->SetPosition(actor->GetPosition().x, actor->GetPosition().y);

		(boost::shared_dynamic_cast<behaviour::Bullet, Behaviour>(bullet->GetBehaviour()))->SetGunslinger(actor->GetBehaviour());
		actor->GetLevel()->GetLayer("Bullets")->Add(bullet);
	}

	int		Weapon::GetAmmo()
	{
		return mAmmo;
	}

	void	Weapon::SetAmmo(int count)
	{
		mAmmo = min(count, mMaxAmmo);
	}

	int		Weapon::GetMaxAmmo()
	{
		return mMaxAmmo;
	}

	void	Weapon::SetMaxAmmo(int count)
	{
		mMaxAmmo = count;
	}

	void	Weapon::SetInfinity(bool flag)
	{
		isInfinity = flag;
	}

	ItemPtr	CreatePistol()
	{
		Weapon* w = new Weapon();
		w->SetInfinity(true);
		w->SetUseSound("../Data/Sounds/Weapons/Gun.wav");

		return ItemPtr(w);
	}
};