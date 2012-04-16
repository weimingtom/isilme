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
#ifndef ZOMBIELAND_INVENTORY_H
#define ZOMBIELAND_INVENTORY_H

#include "Definitions.h"
#include "Item.h"
#include <list>
#include <map>

namespace inventory
{

/// Класс инвентаря
class ISILME_API Inventory : public boost::enable_shared_from_this<Inventory>
{
public:
	static InventoryPtr New();
	virtual ~Inventory();

	/// Добавляет предмет в инвентарь
	void	AddItem(ItemPtr item);

	/// Экипировать предмет
	void	Equip(ItemPtr item);

	/// Снять предмет
	void	Unequip(Item::Slot slot);

	/// Снять предмет
	void	Unequip(ItemPtr item);

	/// Возвращает экипировку
	ItemPtr	GetSlot(Item::Slot slot);

	/// Возвращает количество предметов
	int		GetItemsCount();

	ItemPtr	GetItem(int number);

	/// Возвращает предмет по тегу
	ItemPtr	GetItemByTag(std::string tag);

	/// Проверяет, экипирован ли слот инвентаря
	bool	IsEquiped(Item::Slot slot);

	/// Удаляет предмет из инвентаря
	void	Remove(ItemPtr item);
protected:
	Inventory();
private:
	std::map<Item::Slot, ItemPtr>	mSlots;
	ItemsList	mItems;
};

};
#endif