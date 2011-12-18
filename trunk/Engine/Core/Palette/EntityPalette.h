#ifndef ISILME_PALETTE_ENTITYPALETTE_H
#define ISILME_PALETTE_ENTITYPALETTE_H

#include "Definitions.h"
class IsilmeExport EntityPalette
{
public:
	typedef std::map<std::string, EntityDefPtr> EntityDefMap;

	EntityPalette();
	virtual ~EntityPalette();

	EntityDefMap* GetData() ;

	void Add(EntityDefPtr def);

	EntityDefPtr Get(std::string type);
private:
	EntityDefMap mPalette;
};
#endif