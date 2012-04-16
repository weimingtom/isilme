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
//	���� ���� � ����� Isilme SDK.
//
//		Isilme SDK - ��������� ���������: �� ������ ������������������ �� �/���
//		�������� �� �� �������� ������� ����������� ������������ �������� GNU � ��� ����,
//		� ����� ��� ���� ������������ ������ ���������� ������������ �����������;
//		���� ������ 3 ��������, ���� (�� ������ ������) ����� ����� �������
//		������.
//
//		Isilme SDK ���������������� � �������, ��� ��� ����� ��������,
//		�� ���� ������ ��������; ���� ��� ������� �������� ��������� ����
//		��� ����������� ��� ������������ �����. ��������� ��. � ������� �����������
//		������������ �������� GNU.
//
//		�� ������ ���� �������� ����� ������� ����������� ������������ �������� GNU
//		������ � ���� ����������. ���� ��� �� ���, ��.
//		<http://www.gnu.org/licenses/>.
#ifndef ZOMBIELAND_INVENTORY_H
#define ZOMBIELAND_INVENTORY_H

#include "Definitions.h"
#include "Item.h"
#include <list>
#include <map>

namespace inventory
{

/// ����� ���������
class ISILME_API Inventory : public boost::enable_shared_from_this<Inventory>
{
public:
	static InventoryPtr New();
	virtual ~Inventory();

	/// ��������� ������� � ���������
	void	AddItem(ItemPtr item);

	/// ����������� �������
	void	Equip(ItemPtr item);

	/// ����� �������
	void	Unequip(Item::Slot slot);

	/// ����� �������
	void	Unequip(ItemPtr item);

	/// ���������� ����������
	ItemPtr	GetSlot(Item::Slot slot);

	/// ���������� ���������� ���������
	int		GetItemsCount();

	ItemPtr	GetItem(int number);

	/// ���������� ������� �� ����
	ItemPtr	GetItemByTag(std::string tag);

	/// ���������, ���������� �� ���� ���������
	bool	IsEquiped(Item::Slot slot);

	/// ������� ������� �� ���������
	void	Remove(ItemPtr item);
protected:
	Inventory();
private:
	std::map<Item::Slot, ItemPtr>	mSlots;
	ItemsList	mItems;
};

};
#endif