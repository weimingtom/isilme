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

	/// Использовать предмет
	void	UseBy(EntityPtr actor);

	/// Возвращает слот, в который экипируется предмет
	Slot	GetSlot();

	/// Возвращает звук использования
	HEFFECT	GetUseSound();

	/// Устанавливает звук использования
	void	SetUseSound(std::string sound);

	/// Возвращает время, затрачиваемое на использование
	float	GetUsingTime();

	/// Возвращает продолжительность перезарядки предмета
	float	GetReloadingTime();

	/// Устанавливает продолжительность использования предмета
	void	SetUsingTime(float time);

	/// Устанавливает продолжительность перезарядки
	void	SetReloadingTime(float time);

	/// Возвращает тип предмета
	std::string	GetTag();

	void	SetTag(std::string tag);

	/// Возвращает иконку предмета
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