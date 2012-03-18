#ifndef ISILME_PALETTE_ENTITYPALETTE_H
#define ISILME_PALETTE_ENTITYPALETTE_H

#include "Definitions.h"
class ISILME_API EntityPalette
{
public:
	typedef std::map<std::string, EntityDefPtr> EntityDefMap;

	EntityPalette();
	virtual ~EntityPalette();

	EntityDefMap* GetData() ;

	/// Adds definition to palette
	void Add(EntityDefPtr def);

	/// Gets definition by type
	EntityDefPtr GetDefinition(std::string type);

	void AddDefinition( EntityDefPtr def );

	/// Creates entity instance with id
	EntityPtr Create(std::string type, std::string id);

	/// Gets instance of entity with id
	EntityPtr GetEntity(std::string name);

	/// Destroy entity with id
	void Destroy(std::string id);

	/// Destroy entity
	void Destroy(EntityPtr entity);
private:
	typedef std::map<std::string, EntityPtr> EntityMap;

	/// Palette
	EntityDefMap mPalette;

	/// Created entities
	EntityMap mEntites;
};
#endif