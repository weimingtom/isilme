#ifndef ZOMBIELAND_ITEM_H
#define ZOMBIELAND_ITEM_H

#include "Definitions.h"

class Item
{
public:
	enum Slot
	{
		Other = 0,
		Weapon = 1,
		Armour = 2
	};
	Item();
	virtual ~Item();

	virtual void	OnUse(EntityPtr actor);

	Slot	GetSlot();

	HEFFECT	GetUseSound();
	void	SetUseSound(std::string sound);
protected:
	void	SetSlot(Slot type);
private:
	std::string mName;
	std::string mDescription;
	bool isQuestItem;
	Slot	mSlot;

	HEFFECT	mUseSound;
};

#endif