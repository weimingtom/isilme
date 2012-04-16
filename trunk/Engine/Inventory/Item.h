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
#ifndef ZOMBIELAND_ITEM_H
#define ZOMBIELAND_ITEM_H

#include "Definitions.h"

namespace inventory
{
class ISILME_API Item : public boost::enable_shared_from_this<Item>
{
	friend class Inventory;
public:
	enum Slot
	{
		Other = 0,
		Weapon = 1,
		Armor = 2,
		Spell = 3,
		Ammo
	};
	Item();
	Item(ItemDef* def);
	virtual ~Item();

	/// ������������ �������
	void	UseBy(EntityPtr actor);

	/// ���������� ����, � ������� ����������� �������
	Slot	GetSlot();

	/// ���������� ���� �������������
	HEFFECT	GetUseSound();

	/// ������������� ���� �������������
	void	SetUseSound(std::string sound);

	/// ���������� �����, ������������� �� �������������
	float	GetUsingTime();

	/// ���������� ����������������� ����������� ��������
	float	GetReloadingTime();

	/// ������������� ����������������� ������������� ��������
	void	SetUsingTime(float time);

	/// ������������� ����������������� �����������
	void	SetReloadingTime(float time);

	/// ���������� ��� ��������
	std::string	GetTag();

	void	SetTag(std::string tag);

	/// ���������� ������ ��������
	gcn::Image*	GetIcon();

	void	SetIcon(std::string fileName);

	bool	IsInfinity();

	void	SetInfinity(bool flag);

	int		GetAmmo();

	int		GetMaxAmmo();

	void	SetAmmo(int count);

	void	SetMaxAmmo(int count);

	InventoryPtr GetInventory();

	std::string	GetGND();

	bool	UseMerging();
protected:
	virtual void	OnAdd();
	virtual void	OnEquip();
	virtual void	OnUnequip();
	virtual void	OnUse(EntityPtr actor);
	void	SetSlot(Slot type);
	
private:
	int mAmmo;
	int mMaxAmmo;
	bool	isInfinity;
	std::string mName;
	std::string mDescription;
	std::string mIcon;
	std::string mTag;
	std::string mGND;
	bool isQuestItem;
	bool useMerging;
	Slot	mSlot;

	float	mUsingTime;
	float	mReloadingTime;

	HEFFECT	mUseSound;
	gcn::Image*	mIconImage;
	InventoryWPtr mInventory;
};

};
#endif