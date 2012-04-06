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
#include "AIBehaviour.h"
#include "Attribute.h"
#include "AIPackage.h"
#include "Palette/AIPalette.h"
#include "Core/FactoryManager.h"
#include "AIBehaviourDef.h"
#include "Fraction.h"
#include "Rank.h"

AIBehaviour::AIBehaviour()
{

}

AIBehaviour::~AIBehaviour()
{

}

AttributePtr AIBehaviour::GetAttribute( std::string id ) const
{
	AttributeMap::const_iterator it = mAttributes.find(id);
	if (it != mAttributes.end())
		return it->second;
	else
		return AttributePtr();
}

void AIBehaviour::AddAttribute(AttributePtr attr )
{
	mAttributes[attr->GetID()] = attr;
}

void AIBehaviour::AddAIPackage( std::string id )
{
	AIPalettePtr palette = FactoryManager::GetSingleton()->GetAIPalette();
	AIPackagePtr package = palette->CreateAIPackage(id);
	if (package)
	{
		AddAIPackage(package);
	}
	else
	{
		// Unknown package id
	}

}

void AIBehaviour::AddAIPackage( AIPackagePtr package )
{
	if (std::find(mActivePackages.begin(), mActivePackages.end(), package) == mActivePackages.end())
		mActivePackages.push_back(package);
}

void AIBehaviour::RemoveAIPackage( AIPackagePtr package )
{
	AIPackageList::iterator it = std::find(mActivePackages.begin(), mActivePackages.end(), package);
	if (it != mActivePackages.end())
		mActivePackages.erase(it);
}

bool AIBehaviour::SendMessage( BehaviourPtr dest, MessageDataPtr data )
{
	return false;
}

void AIBehaviour::OnUpdate( float elapsedTime )
{
	if (GetActiveActionsCount() == 0)
	{
		for (AIPackageList::iterator it = mActivePackages.begin(); it != mActivePackages.end(); ++it)
		{
			AIPackagePtr package = *it;
			if (package->IsApplicable(shared_from_this()))
			{
				ActionPtr action = package->CreateAction();
				if (action)
					StartAction(action);
				break;
			}
		}
	}
}

void AIBehaviour::Init( AIBehaviourDef* def )
{
	// Create attributes
	for (AIBehaviourDef::AttributesList::iterator it = def->attributes.begin(); it != def->attributes.end(); ++it)
	{
		AddAttribute(it->Create());
	}

	// Add AI-packages
	for (AIBehaviourDef::AIPackageList::iterator it = def->AIPackages.begin(); it != def->AIPackages.end(); ++it)
	{
		AddAIPackage(*it);
	}

	// Fractions
	for (AIBehaviourDef::FractionsList::iterator it = def->fractions.begin(); it != def->fractions.end(); ++it)
	{
		SetRank(it->id, it->rank);
	}
}

void AIBehaviour::SetRank(FractionPtr fraction, int rank)
{
	mFractions[fraction] = rank;
}

void AIBehaviour::SetRank(std::string fractionID, int rank)
{
	SetRank(FactoryManager::GetSingleton()->GetFraction(fractionID), rank);
}

int	AIBehaviour::GetRank(FractionPtr fraction) const
{
	std::map<FractionPtr, int>::const_iterator it = mFractions.find(fraction);
	if (it == mFractions.cend())
	{
		return 0;
	}
	else
	{
		return it->second;
	}
}

int	AIBehaviour::GetRank(std::string fractionID) const
{
	return GetRank(FactoryManager::GetSingleton()->GetFraction(fractionID));
}

int AIBehaviour::GetAttitudeTo(AIBehaviourPtr other) const
{
	int attitude = 0;
	int count = 0;

	for (std::map<FractionPtr, int>::const_iterator it1 = mFractions.cbegin(); it1 != mFractions.cend(); ++it1)
	{
		for (std::map<FractionPtr, int>::const_iterator it2 = other->mFractions.cbegin(); it2 != other->mFractions.cend(); ++it2)
		{
			count++;
			if ((*it1).first != 0 && (*it2).first != 0)
			{
				attitude += it1->first->GetAttitudeTo(it2->first);
			}
		}
	}

	if (count != 0)
		attitude /= count;

	return attitude;
}

float AIBehaviour::GetAttributeValue( std::string id ) const
{
	AttributePtr attr = GetAttribute(id);
	if (attr)
		return attr->GetValue();
	else
		return 0.0f;
}
