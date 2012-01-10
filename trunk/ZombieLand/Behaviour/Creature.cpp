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
#include "ZombieLand/Action/Wander.h"
#include "Engine/GUI/ConversationWindow.h"
#include "ZombieLand/State/Play.h"
#include "Query.h"

namespace behaviour
{
	Creature::Creature(CreatureDef* def) : Destroyable(def)
	{
		mConversationID = def->Conversation;
		mMoveAction = action::MovePtr(new action::Move());

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

		//// Пакеты ИИ
		//for (std::list<std::string>::iterator it = def->AIPackages.begin(); it != def->AIPackages.end(); ++it)
		//{
		//	AddAIPackage(*it);
		//}

		// Фракции
		for (std::list<FractionInfo>::iterator it = def->Fractions.begin(); it != def->Fractions.end(); ++it)
		{
			SetRank(it->id, it->rank);
		}

		pw = 0;
		ps = 0;
		isReloading = false;
		mCurrentWeapon = 0;
		mCurrentSpell = 0;
	}

	Creature::~Creature()
	{
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
		UpdateEnemiesList();
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

		// Разговор
		const char* convAttr = element->Attribute("Conversation");
		if (convAttr)
		{
			Conversation = convAttr;
		}
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
		int attitude = 0;
		int count = 0;

		for (std::map<FractionPtr, int>::iterator it1 = mFractions.begin(); it1 != mFractions.end(); ++it1)
		{
			for (std::map<FractionPtr, int>::iterator it2 = other->mFractions.begin(); it2 != other->mFractions.end(); ++it2)
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

	
	void	Creature::SavePoint()
	{
		mCheckPoint = GetActor()->GetPosition();
	}

	void	Creature::Respawn()
	{
		SetActive(true);
		SetHealth(GetMaxHealth());
		GetActor()->SetPosition(mCheckPoint.x, mCheckPoint.y);
		GetActor()->GetBody()->SetActive(true);
	}

	void	Creature::NextWeapon()
	{
		if (GetInventory()->GetItemsCount() == 0)
			return;

		mCurrentWeapon++;
		
		if (mCurrentWeapon >= GetInventory()->GetItemsCount())
			mCurrentWeapon = 0;

		inventory::ItemPtr item = GetInventory()->GetItem(mCurrentWeapon);
		if (item->GetSlot() == inventory::Item::Weapon)
		{
			GetInventory()->Equip(item);
			pw = 0;
		}
		else
		{
			if (pw < GetInventory()->GetItemsCount() + 3)
			{
				pw++;
				NextWeapon();
			}
		}
	}

	void	Creature::NextSpell()
	{
		if (GetInventory()->GetItemsCount() == 0 || ps > GetInventory()->GetItemsCount() + 2)
			return;

		mCurrentSpell++;
		
		if (mCurrentSpell >= GetInventory()->GetItemsCount())
			mCurrentSpell = 0;

		inventory::ItemPtr item = GetInventory()->GetItem(mCurrentSpell);
		if (item->GetSlot() == inventory::Item::Spell)
		{
			GetInventory()->Equip(item);
			ps = 0;
		}
		else
		{
			ps++;
			NextSpell();
		}
	}

	void	Creature::SwitchActivator()
	{
		ActivatorPtr a = Activator::GetActivatorFor(GetActor());
		if (a == 0)
			return;
		a->UseBy(boost::shared_dynamic_cast<Creature>(GetActor()->GetBehaviour()));
	}

	void	Creature::ClearTarget()
	{
		mTarget.reset();
	}

	void	Creature::SetTarget()
	{
		if (mTarget != 0)
		{
			float distance = GetActor()->GetDistanceTo(mTarget);
			if (mTarget->GetBehaviour()->IsActive() && distance <= 4.0f)
				return;
			else
				mTarget.reset();
		}

		float min = 1000;
		Vector2 v = GetActor()->GetPosition();
		QueryPtr targets = GetLevel()->AABBQuery(v.x - 4, v.y - 4, v.x + 4, v.y + 4);


		for (int i = 0; i < targets->GetEntitiesCount(); ++i)
		{
			CreaturePtr c = targets->GetEntity(i)->As<Creature>();
			if (c && c != shared_from_this())
			{
				
				int attitude = GetAttitudeTo(c);
				if (attitude < 0)
				{
					mTarget = targets->GetEntity(i);
				}
			}
		}

	}

	EntityPtr Creature::GetTarget()
	{
		return mTarget;
	}

	void	Creature::UpdateEnemiesList()
	{
		mEnemies.clear();
		Vector2 v = GetActor()->GetPosition();
		QueryPtr targets = GetLevel()->AABBQuery(v.x - 4, v.y - 4, v.x + 4, v.y + 4);

		for (int i = 0; i < targets->GetEntitiesCount(); ++i)
		{
			CreaturePtr c = targets->GetEntity(i)->As<Creature>();
			if (c)
				if (c != shared_from_this() && (GetAttitudeTo(c) < 0))
					mEnemies.push_back(c);
		}
	}

	CreaturePtr Creature::GetEnemy(int index)
	{
		return mEnemies.at(index);
	}

	int	Creature::GetEnemiesCount()
	{
		return mEnemies.size();
	}

	bool Creature::IsUsable()
	{
		return FactoryManager::GetSingleton()->GetConversation(mConversationID) != nullptr;
	}

	void Creature::OnUse(CreaturePtr other)
	{
		story::ConversationPtr conversation = FactoryManager::GetSingleton()->GetConversation(mConversationID);
		if (conversation)
		{
			gcn::Container* w = (gcn::Container*)(ZombieLand::GetSingleton()->playState->GetGUI()->getTop());
			gcn::ConversationWindow* cw = new gcn::ConversationWindow();
			cw->Show(w);
			cw->SetConversation(conversation, GetActor());
			cw->setCaption(GetName());
		}
	}
};