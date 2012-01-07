#ifndef ISILME_FRACTION_H
#define ISILME_FRACTION_

#include "Definitions.h"

///
class ISILME_API Fraction
{
	friend class FactoryManager;
public:
	Fraction();
	virtual ~Fraction();

	/// ���������� ���������� � �����
	RankPtr	GetRankInfo(int rank);

	/// ���������� ������������� �������
	std::string GetID();

	/// ���������� �������� �������
	std::string GetName();

	/// ���������� ��������� � �������
	int	GetAttitudeTo(FractionPtr fraction);

	/// ������������� ��������� � ������ �������
	void SetAttitudeTo(FractionPtr fraction, int value);

	/// ���������� ����� ������������� �������
	int GetAgression();

	/// ���������� ����� �������������
	void SetAgression(int value);
private:
	int mAgression;
	std::string mID;
	std::string mName;
	std::map<int, RankPtr> mRanks;
	std::map<FractionPtr, int> mAttitude;
};
#endif