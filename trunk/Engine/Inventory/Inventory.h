#ifndef ZOMBIELAND_INVENTORY_H
#define ZOMBIELAND_INVENTORY_H

#include "Definitions.h"
#include "Item.h"
#include <list>
#include <map>

namespace inventory
{

/// Класс инвентаря
class IsilmeExport Inventory : public boost::enable_shared_from_this<Inventory>
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