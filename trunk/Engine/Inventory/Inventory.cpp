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
#include "Inventory.h"
#include <algorithm>

namespace inventory
{
InventoryPtr Inventory::New()
{
	Inventory* i = new Inventory();
	return InventoryPtr(i);
}

Inventory::Inventory()
{
}

Inventory::~Inventory()
{
}

bool	Inventory::IsEquiped(Item::Slot slot)
{
	bool r = mSlots.find(slot) != mSlots.end();
	if (r)
	{
		r = mSlots[slot] != 0;
	}
	return r;
}

ItemPtr	Inventory::GetItemByTag(std::string tag)
{
	for (ItemsList::iterator it = mItems.begin(); it != mItems.end(); ++it)
	{
		if ((*it)->GetTag() == tag)
			return *it;
	}

	return ItemPtr();
}

int		Inventory::GetItemsCount()
{
	return mItems.size();
}

ItemPtr	Inventory::GetItem(int number)
{
	return mItems[number];
}

void	Inventory::AddItem(ItemPtr item)
{
	if (item->UseMerging())
	{
		ItemPtr myitem = GetItemByTag(item->GetTag());
		if (myitem)
		{
			// Добавляем зарядов к существующему
			myitem->SetAmmo(item->GetAmmo() + myitem->GetAmmo());
			return;
		}
	}

	// Добавляем предмет в инвентарь
	mItems.push_back(item);
	item->mInventory = shared_from_this();
	item->OnAdd();
}

void	Inventory::Unequip(Item::Slot slot)
{
	ItemPtr item = GetSlot(slot);
	if (item != 0)
	{
		mSlots.erase(mSlots.find(slot));
		item->OnUnequip();
	}
}

void	Inventory::Unequip(ItemPtr item)
{
	if (GetSlot(item->GetSlot()) == item)
	{
		mSlots.erase(mSlots.find(item->GetSlot()));
		item->OnUnequip();
	}
}

void	Inventory::Equip(ItemPtr item)
{
	if (std::find(mItems.begin(), mItems.end(), item) == mItems.end())
		AddItem(item);

	Unequip(item->GetSlot());
	mSlots[item->GetSlot()] = item;
	item->OnEquip();
}

ItemPtr	Inventory::GetSlot(Item::Slot slot)
{
	return mSlots[slot];
}

void	Inventory::Remove(ItemPtr item)
{
	if (GetSlot(item->GetSlot()) == item)
	{
		Unequip(item->GetSlot());
	}

	ItemsList::iterator it = std::find(mItems.begin(), mItems.end(), item);
	if (it != mItems.end())
		mItems.erase(it);
}
};