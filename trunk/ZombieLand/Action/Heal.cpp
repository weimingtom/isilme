#include "ZombieLand.h"
#include "ZombieLand/Action/Heal.h"
#include "../Core/Entity.h"
#include "../Behaviour/Creature.h"
#include "UseItem.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"

namespace action
{
	Heal::Heal()
	{
		mSpeed = 20.0f;
		mCost = 40.0f;
		SetDuration(1.0f);
	}

	Heal::~Heal()
	{
	}

	float Heal::GetCost()
	{
		return mCost;
	}

	void	Heal::OnStart()
	{

	}

	void Heal::OnUpdate(float elapsedTime)
	{
		GetEntity()->As<behaviour::Creature>()->SetHealth(GetEntity()->As<behaviour::Creature>()->GetHealth() + mSpeed * elapsedTime);
	}

	HealPackage::HealPackage()
	{

	}

	HealPackage::~HealPackage()
	{

	}

	bool HealPackage::IsApplicable( BehaviourPtr b ) const
	{
		actor = b->GetEntity()->As<behaviour::Creature>();
		
		return (actor->GetHealth() < 0.5f * actor->GetMaxHealth()) && (actor->GetInventory()->GetItemByTag("Heal") != nullptr) ;
	}

	ActionPtr HealPackage::CreateAction() const
	{
		inventory::ItemPtr it = actor->GetInventory()->GetItemByTag("Heal");
		UseItem* a = new UseItem(it);
		return ActionPtr(a);
	}



	HealPackageDef::HealPackageDef()
	{

	}

	HealPackageDef::~HealPackageDef()
	{

	}

	void HealPackageDef::Parse( TiXmlElement* element )
	{

	}

	AIPackagePtr HealPackageDef::CreatePackage()
	{
		return AIPackagePtr(new HealPackage());
	}

};