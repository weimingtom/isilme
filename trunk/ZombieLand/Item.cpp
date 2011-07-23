#include "ZombieLand.h"
#include "Item.h"

Item::Item()
{
	mUseSound = 0;
}

Item::~Item()
{
}

void	Item::OnUse(EntityPtr actor)
{
}

Item::Slot	Item::GetSlot()
{
	return mSlot;
}

void	Item::SetSlot(Item::Slot type)
{
	mSlot = type;
}

HEFFECT	Item::GetUseSound()
{
	return mUseSound;
}

void	Item::SetUseSound(std::string sound)
{
	HEFFECT eff = Engine::GetSingleton()->GetResourceManager()->GetEffect(sound);
	mUseSound = eff;
}