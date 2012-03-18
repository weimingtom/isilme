#ifndef ISILME_PALETTE_FRACTIONSPALETTE_H
#define ISILME_PALETTE_FRACTIONSPALETTE_H

#include "Definitions.h"

class ISILME_API FractionsPalette
{
public:
	FractionsPalette();
	virtual ~FractionsPalette();

	/// Adds fraction 
	void AddFraction(FractionPtr fraction);

	/// Gets fraction by id
	FractionPtr GetFraction(std::string id);
private:
	typedef std::map<std::string, FractionPtr> FractionMap;

	/// Fractions paltte id - fraction
	FractionMap mFractions;
};

#endif