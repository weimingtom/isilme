#ifndef ISILME_PALETTE_PALETTE_H
#define ISILME_PALETTE_PALETTE_H

template <typename ItemType, typename DefType, typename FactoryType, boost::shared_ptr<ItemType> ItemTypePtr>
class Palette
{
public:
	ItemTypePtr Create();
};
#endif