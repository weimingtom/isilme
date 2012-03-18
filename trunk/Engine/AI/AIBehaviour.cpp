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
		mActivePackages.push_front(package);
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
				StartAction(package->CreateAction());
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
