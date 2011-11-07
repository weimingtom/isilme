#include "Isilme.h"
#include "Fraction.h"
#include "Rank.h"

Fraction::Fraction()
{
}

Fraction::~Fraction()
{
}

std::string Fraction::GetID()
{
	return mID;
}

RankPtr	Fraction::GetRankInfo(int rank)
{
	std::map<int, RankPtr>::iterator it = mRanks.find(rank);
	if (it != mRanks.end())
	{
		return it->second;
	}
	else
		return RankPtr();
}

std::string Fraction::GetName()
{
	return mName;
}

int	Fraction::GetAttitudeTo(FractionPtr fraction)
{
	if (mAttitude.find(fraction) != mAttitude.end())
		return mAttitude[fraction];// - mAgression;
	else if (fraction.get() == this)
		return 100;
	else
		return -GetAgression();
}

void	Fraction::SetAttitudeTo(FractionPtr fraction, int value)
{
	mAttitude[fraction] = value;
}

int		Fraction::GetAgression()
{
	return mAgression;
}