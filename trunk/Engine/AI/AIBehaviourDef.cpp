//  Copyright (C) 2010-2012 Alexander Alimov
//
//	This file is part of Isilme SDK.
//
//		Isilme SDK is free software: you can redistribute it and/or modify
//		it under the terms of the GNU Lesser General Public License as published by
//		the Free Software Foundation, either version 3 of the License, or
//		(at your option) any later version.
//
//		Isilme SDK is distributed in the hope that it will be useful,
//		but WITHOUT ANY WARRANTY; without even the implied warranty of
//		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//		GNU Lesser General Public License for more details.
//
//		You should have received a copy of the GNU Lesser General Public License
//		along with Isilme SDK.  If not, see <http://www.gnu.org/licenses/>.
//
//	Этот файл — часть Isilme SDK.
//
//		Isilme SDK - свободная программа: вы можете перераспространять ее и/или
//		изменять ее на условиях Меньшей стандартной общественной лицензии GNU в том виде,
//		в каком она была опубликована Фондом свободного программного обеспечения;
//		либо версии 3 лицензии, либо (по вашему выбору) любой более поздней
//		версии.
//
//		Isilme SDK распространяется в надежде, что она будет полезной,
//		но БЕЗО ВСЯКИХ ГАРАНТИЙ; даже без неявной гарантии ТОВАРНОГО ВИДА
//		или ПРИГОДНОСТИ ДЛЯ ОПРЕДЕЛЕННЫХ ЦЕЛЕЙ. Подробнее см. в Меньшей стандартной
//		общественной лицензии GNU.
//
//		Вы должны были получить копию Меньшей стандартной общественной лицензии GNU
//		вместе с этой программой. Если это не так, см.
//		<http://www.gnu.org/licenses/>.
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
