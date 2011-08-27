#include "Isilme.h"
#include "Item.h"
#include "Inventory.h"

namespace inventory
{
Item::Item()
{
	mUseSound = 0;
	mUsingTime = 0.0f;
	mReloadingTime = 0.0f;
	mIcon = "";
	mAmmo = 0;
	mMaxAmmo = 0;
	isInfinity = true;
	mIconImage = 0;
	mTag = "";
}

Item::Item(ItemDef* def)
{
	mUseSound = def->UseSound;
	mUsingTime = def->UsingTime;
	mReloadingTime = def->ReloadingTime;
	mAmmo = def->Ammo;
	mMaxAmmo = def->MaxAmmo;
	isInfinity = def->Infinity;
	mIconImage = def->Icon;
	mTag = def->Tag;

	mGND = def->GND;
	useMerging = def->UseMerging;

	mIcon = "";
}

Item::~Item()
{
}

std::string Item::GetGND()
{
	return mGND;
}

std::string	Item::GetTag()
{
	return mTag;
}

void	Item::SetTag(std::string tag)
{
	mTag = tag;
}

void	Item::OnAdd()
{
}

void	Item::OnEquip()
{
}

void	Item::OnUnequip()
{
}

void	Item::UseBy(EntityPtr entity)
{
	if (!isInfinity)
	{
		if (mAmmo <= 0)
			return;
		mAmmo--;
	}

	if (GetUseSound())
		Engine::GetSingleton()->GetSoundSystem()->PlayEffect(GetUseSound());

	OnUse(entity);
}

bool	Item::UseMerging()
{
	return useMerging;
}

InventoryPtr	Item::GetInventory()
{
	return mInventory.lock();
}

int		Item::GetAmmo()
{
	return mAmmo;
}

void	Item::SetAmmo(int count)
{
	mAmmo = min(count, mMaxAmmo);
}

int		Item::GetMaxAmmo()
{
	return mMaxAmmo;
}

void	Item::SetMaxAmmo(int count)
{
	mMaxAmmo = count;
}

void	Item::SetInfinity(bool flag)
{
	isInfinity = flag;
}

gcn::Image* Item::GetIcon()
{
	if (mIconImage == 0)
		mIconImage = gcn::Image::load(mIcon.c_str());
	return mIconImage;
}

void	Item::SetIcon(std::string fileName)
{
	mIcon = fileName;
}

float	Item::GetUsingTime()
{
	return mUsingTime;
}

float	Item::GetReloadingTime()
{
	return mReloadingTime;
}

void	Item::SetUsingTime(float time)
{
	mUsingTime = time;
}

void	Item::SetReloadingTime(float time)
{
	mReloadingTime = time;
}

bool	Item::IsInfinity()
{
	return isInfinity;
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
};