#include "IsilmePCH.h"
#include "FractionsPalette.h"
#include "Fraction.h"

FractionsPalette::FractionsPalette()
{

}

FractionsPalette::~FractionsPalette()
{

}

void FractionsPalette::AddFraction( FractionPtr fraction )
{
	mFractions[fraction->GetID()] = fraction;
}

FractionPtr FractionsPalette::GetFraction( std::string id )
{
	FractionMap::iterator it = mFractions.find(id);
	if (it != mFractions.end())
		return it->second;
	return FractionPtr();
}
