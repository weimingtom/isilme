#ifndef ZOMBIELAND_INVENTORY_H
#define ZOMBIELAND_INVENTORY_H

#include "Definitions.h"
#include "Item.h"
#include <list>
#include <map>

class Inventory : public boost::enable_shared_from_this<Inventory>
{
public:
	static InventoryPtr New();
	virtual ~Inventory();

	/// ��������� ������� � ���������
	void	AddItem(ItemPtr item);

	/// ����������� �������
	void	Equip(ItemPtr item);

	void	Unequip(Item::Slot slot);

	void	Unequip(ItemPtr item);

	/// ���������� ����������
	ItemPtr	GetSlot(Item::Slot slot);

	int		GetItemsCount();

	ItemPtr	GetItem(int number);

	ItemPtr	GetItemByTag(std::string tag);

	bool	IsEquiped(Item::Slot slot);
protected:
	Inventory();
private:
	std::map<Item::Slot, ItemPtr>	mSlots;
	ItemsList	mItems;
};
#endif