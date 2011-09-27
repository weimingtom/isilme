#ifndef ISILME_FRACTION_H
#define ISILME_FRACTION_

#include "Definitions.h"

///
class IsilmeExport Fraction
{
public:
	Fraction();
	virtual ~Fraction();

	/// Возвращает информацию о ранге
	RankPtr	GetRankInfo(int rank);

	/// Возвращает идентификатор фракции
	std::string GetID();

	/// Возвращает название фракции
	std::string GetName();
private:
	std::string mID;
	std::string mName;
	std::map<int, RankPtr> mRanks;
};

#endif