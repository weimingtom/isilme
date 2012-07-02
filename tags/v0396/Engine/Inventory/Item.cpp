//  Copyright (C) 2010-2012 VSTU
//
//	This file is part of Isilme SDK.
//
//		Isilme SDK is free software: you can redistribute it and/or modify
//		it under the terms of the GNU Lesser General Public License as published by
//		the Free Software Foundation, either version 3 of the License, or
//		(at your option) any later version.
//
//		Isilme SDK is distributed in the hope that it will be useful,
//		but WITHOUT ANY WARRANTY; without even the implied warranty of
//		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//		GNU Lesser General Public License for more details.
//
//		You should have received a copy of the GNU Lesser General Public License
//		along with Isilme SDK.  If not, see <http://www.gnu.org/licenses/>.
//
//	Этот файл — часть Isilme SDK.
//
//		Isilme SDK - свободная программа: вы можете перераспространять ее и/или
//		изменять ее на условиях Меньшей стандартной общественной лицензии GNU в том виде,
//		в каком она была опубликована Фондом свободного программного обеспечения;
//		либо версии 3 лицензии, либо (по вашему выбору) любой более поздней
//		версии.
//
//		Isilme SDK распространяется в надежде, что она будет полезной,
//		но БЕЗО ВСЯКИХ ГАРАНТИЙ; даже без неявной гарантии ТОВАРНОГО ВИДА
//		или ПРИГОДНОСТИ ДЛЯ ОПРЕДЕЛЕННЫХ ЦЕЛЕЙ. Подробнее см. в Меньшей стандартной
//		общественной лицензии GNU.
//
//		Вы должны были получить копию Меньшей стандартной общественной лицензии GNU
//		вместе с этой программой. Если это не так, см.
//		<http://www.gnu.org/licenses/>.
#include "IsilmePCH.h"
#include "Item.h"
#include "Inventory.h"
#include "ItemDef.h"
#include "Core/SoundSystem.h"
#include "Core/ResourceManager.h"

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
	mAmmo = std::min(count, mMaxAmmo);
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
	{
		if (mIcon == "")
			mIcon = "../Data/Icons/Empty.png";
		mIconImage = gcn::Image::load(mIcon.c_str());
	}
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