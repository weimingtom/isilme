#include "ZombieLand.h"
#include "Die.h"
#include "ZombieLand/LootTable.h"
#include "ZombieLand/Behaviour/Item.h"

namespace action
{
	Die::Die()
	{
		SetDuration(1.0f);
		mEffect = 0;
	}

	Die::~Die()
	{
	}

	void	Die::OnDone()
	{
		GetActor()->GetBehaviour()->SetActive(false);

		LootTablePtr lootTable = GetEntity()->As<behaviour::Destroyable>()->GetLootTable();
		if (lootTable)
		{
			std::list<Loot> lootList;
			lootTable->GenerateLoot(&lootList);

			for (std::list<Loot>::iterator it = lootList.begin(); it != lootList.end(); ++it)
			{
				EntityPtr e = GetLevel()->CreateEntity(it->Item, GetActor()->GetPosition().x, GetActor()->GetPosition().y, GetActor()->GetAngle(), "");
				e->As<behaviour::Item>()->SetAmmo(it->Ammo);
			}
		}
	}

	void	Die::OnStart()
	{
		GetActor()->GetBody()->SetActive(false);

		if (mEffect != 0)
		Engine::GetSingleton()->GetSoundSystem()->PlayEffect(mEffect);

		GetLevel()->GetLayer("Grass")->Add(GetActor());
	}

	void	Die::SetSound(std::string sound)
	{
		mEffect = Engine::GetSingleton()->GetResourceManager()->GetEffect(sound);
	}
};