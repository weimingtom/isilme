#include "IsilmePCH.h"
#include "AIBehaviourDef.h"


void AIBehaviourDef::Parse( TiXmlElement* element )
{
	/// Fractions
	TiXmlElement* fractionsElement = element->FirstChildElement("Fractions");
	if (fractionsElement)
		ParseFractions(fractionsElement);

	/// Packages
	TiXmlElement* AIElement = element->FirstChildElement("AI");
	if (AIElement)
		ParseAIPackages(AIElement);

	// Attributes
	TiXmlElement* attributesElement = element->FirstChildElement("Attributes");
	if (attributesElement)
		ParseAttributes(attributesElement);
}


void AIBehaviourDef::ParseAttributes( TiXmlElement* attributesElement )
{
	TiXmlElement* attributeElement = attributesElement->FirstChildElement("Attribute");
	while (attributeElement)
	{
		AttributeDef attrDef;
		attrDef.Parse(attributeElement);
		attributes.push_back(attrDef);
		attributeElement = attributeElement->NextSiblingElement("Attribute");
	}
}

void AIBehaviourDef::ParseAIPackages( TiXmlElement* AIElement )
{
	if (!AIElement)
		return;

	TiXmlElement* packageElement = AIElement->FirstChildElement("Package");
	while (packageElement)
	{
		const char* idAttr = packageElement->Attribute("ID");

		if (idAttr)
			AIPackages.push_back(idAttr);

		packageElement = packageElement->NextSiblingElement("Package");
	}
}

void AIBehaviourDef::ParseFractions( TiXmlElement* fractionsElement )
{
	if (!fractionsElement)
		return;

	TiXmlElement* fractionElement = fractionsElement->FirstChildElement("Fraction");
	while (fractionElement)
	{
		const char* idAttr = fractionElement->Attribute("ID");
		if (idAttr)
		{
			FractionInfo f;
			f.id = idAttr;
			f.rank = 1;
			fractionElement->QueryIntAttribute("Rank", &f.rank);

			fractions.push_back(f);
		}

		fractionElement = fractionElement->NextSiblingElement("Fraction");
	}
}
