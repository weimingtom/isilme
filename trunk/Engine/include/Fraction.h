#ifndef ISILME_FRACTION_H
#define ISILME_FRACTION_

#include "Definitions.h"

///
class IsilmeExport Fraction
{
public:
	Fraction();
	virtual ~Fraction();

	/// ���������� ���������� � �����
	RankPtr	GetRankInfo(int rank);

	/// ���������� ������������� �������
	std::string GetID();

	/// ���������� �������� �������
	std::string GetName();
private:
	std::string mID;
	std::string mName;
	std::map<int, RankPtr> mRanks;
};

#endif