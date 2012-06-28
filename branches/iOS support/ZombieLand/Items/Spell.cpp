#include "ZombieLand.h"
#include "Spell.h"
#include "ZombieLand/Action/Heal.h"
#include "ZombieLand/Action/Wind.h"
#include "ZombieLand/Action/Shild.h"

namespace inventory
{
	SpellDef::SpellDef()
	{
	}

	SpellDef::~SpellDef()
	{
	}

	void	SpellDef::Parse(TiXmlElement* def)
	{
		ItemDef::Parse(def);
		if (def->Attribute("Action"))
			Action = def->Attribute("Action");
	}

	ItemPtr	SpellDef::Create()
	{
		return ItemPtr(new Spell(this));
	}

	Spell::Spell(SpellDef* def) : Item(def)
	{
		SetSlot(Item::Spell);

		if (def->Action == "Wind")
		{
			SetAction(ActionPtr(new action::Wind()));
		}
		else if (def->Action == "Heal")
		{
			SetAction(ActionPtr(new action::Heal()));
		}
		if (def->Action == "Shild")
		{
			SetAction(ActionPtr(new action::Shild()));
		}
		else
		{
		}
	}

	Spell::~Spell()
	{
	}

	void	Spell::SetAction(ActionPtr action)
	{
		mAction = action;
		SetUsingTime(action->GetDuration());
		SetReloadingTime(0.0f);
	}

	void	Spell::OnUse(EntityPtr actor)
	{
		if (IsContinuous())
		{
			if (mAction->IsActive())
				mAction->Stop();
			else
				actor->GetBehaviour()->StartAction(mAction);
		}
		else
		{
			actor->GetBehaviour()->StartAction(mAction);
		}

		if (GetAmmo() == 0)
			GetInventory()->Remove(shared_from_this());
	}

	void	Spell::SetContinuous(bool flag)
	{
		isContinuous = flag;
	}

	bool	Spell::IsContinuous()
	{
		return isContinuous;
	}
};