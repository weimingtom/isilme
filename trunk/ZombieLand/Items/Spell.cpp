#include "ZombieLand.h"
#include "Spell.h"

namespace items
{
	Spell::Spell()
	{
		SetSlot(Item::Spell);
	}

	Spell::~Spell()
	{
	}

	void	Spell::SetAction(ActionPtr action)
	{
		mAction = action;
		SetUsingTime(action->GetDoingTime());
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