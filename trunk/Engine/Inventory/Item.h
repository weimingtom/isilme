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