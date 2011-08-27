#ifndef ZOMBIELAND_ITEM_H
#define ZOMBIELAND_ITEM_H

#include "Definitions.h"
#include "Isilme.h"
#include <guichan.hpp>

namespace inventory
{
class IsilmeExport Item : public boost::enable_shared_from_this<Item>
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