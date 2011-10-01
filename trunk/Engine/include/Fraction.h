#ifndef ISILME_FRACTION_H
#define ISILME_FRACTION_

#include "Definitions.h"

///
class IsilmeExport Fraction
{
	friend class FactoryManager;
public:
	Fraction();
	virtual ~Fraction();

	/// Возвращает информацию о ранге
	RankPtr	GetRankInfo(int rank);

	/// Возвращает идентификатор фракции
	std::string GetID();

	/// Возвращает название фракции
	std::string GetName();

	/// Возвращает отношение к фракции
	int	GetAttitudeTo(FractionPtr fraction);

	/// Устанавливает отношение к другой фракции
	void SetAttitudeTo(FractionPtr fraction, int value);
private:
	std::string mID;
	std::string mName;
	std::map<int, RankPtr> mRanks;
	std::map<FractionPtr, int> mAttitude;
};
#endif