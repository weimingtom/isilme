#ifndef ISILME_AI_AIBEHAVIOURDEF_H
#define ISILME_AI_AIBEHAVIOURDEF_H

#include "AITypes.h"
#include "AttributeDef.h"

class ISILME_API AIBehaviourDef
{
public:
	void	Parse(TiXmlElement* element);

	typedef struct FractionInfo
	{
	public:
		std::string id;
		int	rank;
	} FractionInfo;

	typedef std::vector<AttributeDef> AttributesList;
	typedef std::vector<std::string> AIPackageList;
	typedef std::vector<FractionInfo> FractionsList;

	/// Fractions and ranks
	FractionsList fractions;

	/// Definitions of attributes
	AttributesList attributes;

	/// List of AI-packages identifiers
	AIPackageList AIPackages;


private:
	/// Parses attributes from XML
	void	ParseAttributes(TiXmlElement* attributesElement);

	/// Parses AI-packages from XML
	void	ParseAIPackages(TiXmlElement* aiElement);

	/// Parses fractions info
	void	ParseFractions(TiXmlElement* fractionsElement);
};

#endif