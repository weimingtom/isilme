#ifndef ISILME_AI_RANK_H
#define ISILME_AI_RANK_H

#include "Definitions.h"

class IsilmeExport Rank
{
	friend class FactoryManager;
public:
	Rank();
	virtual ~Rank();

	/// ���������� ������������� 
	int GetID();

	/// ���������� �������
	///FractionPtr	GetFraction();
private:
	int mID;
};
#endif