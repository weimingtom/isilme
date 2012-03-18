#ifndef ISILME_AI_RANK_H
#define ISILME_AI_RANK_H

#include "Definitions.h"
#include "../Serialisation/Types.h"

class ISILME_API Rank
{
	friend class FactoryManager;
	friend class serialisation::FractionsLoader;
public:
	Rank();
	virtual ~Rank();

	/// Возвращает идентификатор 
	int GetID();

	/// Возвращает фракцию
	///FractionPtr	GetFraction();
private:
	int mID;
};
#endif