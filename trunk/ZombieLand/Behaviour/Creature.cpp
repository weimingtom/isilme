#include "ZombieLand.h"
#include "ZombieLand/Behaviour/Creature.h"
#include "ZombieLand/Action/Move.h"
#include "ZombieLand/Action/Attack.h"
#include "ZombieLand/Action/UseItem.h"
#include "ZombieLand/Items/Weapon.h"
#include "Engine/Inventory/Item.h"
#include "Engine/include/Fraction.h"
#include "Engine/include/Rank.h"
#include "Engine/include/AIPackage.h"

namespace behaviour
{
	Creature::Creature(CreatureDef* def) : Destroyable(def)
	{
		mMoveAction = action::MovePtr(new action::Move());
		SetAttribute(Speed, 3);

		mMoveBack = action::MovePtr(new action::Move());
		//mMoveBack->SetSpeed(-2.0f);

		mAttack = action::AttackPtr(new action::Attack());


		mEnergy = def->Energy;
		mMaxEnergy = def->MaxEnergy;
		mEnergyResoration = def->EnergyRestoration;

		mShotAction = action::UseItem::New(inventory::Item::Weapon, GetInventory());
		mReloadAction = action::UseItem::New(inventory::Item::Ammo, GetInventory());
		mSpellAction = action::UseItem::New(inventory::Item::Spell, GetInventory());

		onThink = def->OnThink;

		// Пакеты ИИ
		for (std::list<std::string>::iterator it = def->AIPackages.begin(); it != def->AIPackages.end(); ++it)
		{
			AddAIPackage(*it);
		}
	}

	Creature::~Creature()
	{
	}

	float	Creature::GetAttribute(Attribute attr)
	{
		return mAttributes[attr];
	}

	void	Creature::SetAttribute(Attribute attr, float value)
	{
		mAttributes[attr] = value;
	}

	ActionPtr	Creature::GetSpellAction()
	{
		return mSpellAction;
	}

	ActionPtr	Creature::GetReloadAction()
	{
		return mReloadAction;
	}

	void	Creature::SetMaxEnergy(float energy)
	{
		mMaxEnergy = energy;
	}

	float Creature::GetMaxEnergy()
	{
		return mMaxEnergy;
	}

	void	Creature::SetEnergy(float energy)
	{
		mEnergy = energy;
	}

	float	Creature::GetEnergy()
	{
		return mEnergy;
	}

	void	Creature::Think(float elapsedTime)
	{
		Destroyable::Think(elapsedTime);
		if (mEnergy < mMaxEnergy)
			mEnergy += mEnergyResoration * elapsedTime;

		if (onThink)
		{
			onThink(GetActor()->As<Creature>(), elapsedTime);
		}
	}

	BehaviourPtr CreatureDef::Create()
	{
		return BehaviourPtr(new Creature(this));
	}

	void	CreatureDef::Parse(TiXmlElement* element)
	{
		DestroyableDef::Parse(element);
		Energy = 100.0f;
		MaxEnergy = 100.0f;
		EnergyRestoration = 2.0f;

		element->QueryFloatAttribute("Energy", &Energy);
		element->QueryFloatAttribute("MaxEnergy", &MaxEnergy);
		element->QueryFloatAttribute("EnergyRestoration", &EnergyRestoration);

		if (element->Attribute("OnThink"))
		{
			OnThink = ScriptAPI::MakeFunction("me, elapsedTime", element->Attribute("OnThink"));
		}

		/// Фракции
		TiXmlElement* fractionsElement = element->FirstChildElement("Fractions");
		if (fractionsElement)
			ParseFractions(fractionsElement);

		/// ИИ
		TiXmlElement* AIElement = element->FirstChildElement("AI");
		if (AIElement)
			ParseAI(AIElement);
	}

	void	CreatureDef::ParseFractions(TiXmlElement* fractionsElement)
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

				Fractions.push_back(f);
			}

			fractionElement = fractionElement->NextSiblingElement("Fraction");
		}
	}

	void	CreatureDef::ParseAI(TiXmlElement* AIElement)
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

	action::MovePtr	Creature::GetMoveAction()
	{
		return mMoveAction;
	}

	ActionPtr	Creature::GetShotAction()
	{
		return mShotAction;
	}

	action::MovePtr	Creature::GetMoveBackAction()
	{
		return mMoveBack;
	}

	action::AttackPtr Creature::GetAttackAction()
	{
		return mAttack;
	}

	void Creature::RotateToPoint(Vector2 target)
	{
		Vector2 position = GetActor()->GetPosition();
		Vector2 d = target - position;

		float sina = d.y / d.Length();
		float cosa = d.x / d.Length();

		if (d.Length() < 0.2f)
			return;

		float a = asin(sina);

		if (sina >= 0.0f && cosa >= 0.0f)
		{
			GetActor()->SetAngle(a);
		}
		else if (sina >= 0.0f && cosa <= 0.0f)
		{
			GetActor()->SetAngle(3.14 - a);
		}
		else if (sina <= 0.0f && cosa <= 0.0f)
		{
			GetActor()->SetAngle(3.14f - a);
		}
		else 
		{
			GetActor()->SetAngle(a);
		}
	}

	int	Creature::GetRank(FractionPtr fraction)
	{
		std::map<FractionPtr, int>::iterator it = mFractions.find(fraction);
		if (it == mFractions.end())
		{
			return 0;
		}
		else
		{
			return it->second;
		}
	}

	int	Creature::GetRank(std::string fractionID)
	{
		return GetRank(FactoryManager::GetSingleton()->GetFraction(fractionID));
	}

	void Creature::SetRank(FractionPtr fraction, int rank)
	{
		mFractions[fraction] = rank;
	}

	void Creature::SetRank(std::string fractionID, int rank)
	{
		SetRank(FactoryManager::GetSingleton()->GetFraction(fractionID), rank);
	}

	int Creature::GetAttitudeTo(CreaturePtr other)
	{
		int attitude = 100;

		for (std::map<FractionPtr, int>::iterator it1 = mFractions.begin(); it1 != mFractions.end(); ++it1)
		{
			for (std::map<FractionPtr, int>::iterator it2 = other->mFractions.begin(); it2 != other->mFractions.end(); ++it2)
			{
				int a = it1->first->GetAttitudeTo(it2->first);
				if (a < attitude)
					attitude = a;
			}
		}

		if (mFractions.size() == 0)
			attitude = 0;

		return attitude;
	}

	void	Creature::AddAIPackage(AIPackagePtr package, int priority)
	{
		mAIPackages.push_back(package);
	}

	void	Creature::AddAIPackage(std::string packageID, int priority)
	{
		AIPackagePtr package = FactoryManager::GetSingleton()->GetAIPackage(packageID);
		if (package)
		{
			AddAIPackage(package, priority);
		}
		else
		{
			LOG_W("AI package %s not found", packageID.c_str());
		}
	}
};