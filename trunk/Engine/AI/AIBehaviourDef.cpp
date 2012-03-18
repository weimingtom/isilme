#include "IsilmePCH.h"
#include "AIBehaviourDef.h"


void AIBehaviourDef::Parse( TiXmlElement* element )
{
	/// �������
	TiXmlElement* fractionsElement = element->FirstChildElement("Fractions");
	if (fractionsElement)
		ParseFractions(fractionsElement);

	/// ��
	TiXmlElement* AIElement = element->FirstChildElement("AI");
	if (AIElement)
		ParseAIPackages(AIElement);
}


void AIBehaviourDef::ParseAttributes( TiXmlElement* attributesElement )
{

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
