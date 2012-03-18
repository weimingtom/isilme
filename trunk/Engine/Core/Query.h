#ifndef ISILME_QUERY_RESULT_H
#define ISILME_QUERY_RESULT_H

#include "Definitions.h"



/// Query result.
class ISILME_API Query
{
public:

	/// Default constructor.
	Query();
		
	/// Destructor.
	virtual ~Query();
	
	/// Gets an entity.
	///
	/// @param	index	Zero-based index of the entity in result.
	///
	/// @return	The entity or null.
	EntityPtr GetEntity(int index);

	/// Gets the entities count.
	///
	/// @return	The entities count.
	int GetEntitiesCount();

	/// Executes this object.
	virtual bool Execute() = 0;
protected:
	/// Pushes an entity.
	///
	/// @param	entity	The entity.
	void PushEntity(EntityPtr entity);

	/// Clears this object to its blank/initial state.
	void Clear();
private:
	/// The entities
	std::vector<EntityPtr> mEntities;
};

#endif