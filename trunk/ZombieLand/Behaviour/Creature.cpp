#include "ZombieLand.h"
#include "ZombieLand/Behaviour/Creature.h"
#include "ZombieLand/Action/Move.h"
#include "ZombieLand/Action/Attack.h"
#include "ZombieLand/Action/UseItem.h"
#include "ZombieLand/Items/Weapon.h"
#include "ZombieLand/Action/Wander.h"
#include "Engine/GUI/ConversationWindow.h"
#include "ZombieLand/State/Play.h"
#include "Query.h"
#include "Engine/ScriptAPI.h"

namespace action
{
	class SpeakAction : public Action
	{
	public:
		SpeakAction()
		{
			SetDuration(Action::InfiniteDuration);
		}

		virtual bool DoneCondition() override
		{
			return false;
		}
	};
}
namespace behaviour
{
	Creature::Creature()
	{
		mMoveAction = action::MovePtr(new action::Move());

		mMoveBack = action::MovePtr(new action::Move());
		//mMoveBack->SetSpeed(-2.0f);

		mAttack = action::AttackPtr(new action::Attack());



		mShotAction = action::UseItem::New(inventory::Item::Weapon, GetInventory());
		mReloadAction = action::UseItem::New(inventory::Item::Ammo, GetInventory());
		mSpellAction = action::UseItem::New(inventory::Item::Spell, GetInventory());
		mDieAction = action::DiePtr(new action::Die());

		pw = 0;
		ps = 0;
		isReloading = false;
		mCurrentWeapon = 0;
		mCurrentSpell = 0;
	}

	Creature::~Creature()
	{
	}

	void Creature::Init(CreatureDef* def)
	{
		Container::Init(&def->containerDef);
		AIBehaviour::Init(&def->AIDef);
		Destroyable::Init(&def->destroyableDef);
		story::ConversationPtr conversation = story::Conversation::Get(def->Conversation);
		SetConversation(conversation);

		mEnergy = def->Energy;
		mMaxEnergy = def->MaxEnergy;
		mEnergyResoration = def->EnergyRestoration;
		onThink = def->OnThink;
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

	void	Creature::OnUpdate(float elapsedTime)
	{
		//if (GetHealth() < 0.0f)
		//{
		//	OnDie();
		//	return;
		//}
		
		AIBehaviour::OnUpdate(elapsedTime);

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
		boost::shared_ptr<Creature> c(new Creature());
		c->Init(this);

		return c;
	}

	void	CreatureDef::Parse(TiXmlElement* element)
	{
		AIDef.Parse(element);
		containerDef.Parse(element);
		destroyableDef.Parse(element);
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



		// Разговор
		const char* convAttr = element->Attribute("Conversation");
		if (convAttr)
		{
			Conversation = convAttr;
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
		return GetConversation() != nullptr;
	}

	void Creature::OnUse(CreaturePtr other)
	{
		story::ConversationPtr conversation = GetConversation();
		if (conversation)
		{
			StartConversationWith(other);
		}
	}

	ActionPtr Creature::GetDieAction()
	{
		return mDieAction;
	}

	void Creature::OnDie()
	{
		StartAction(ActionPtr(new action::Die()));
	}

	void Creature::OnGotDamage( const float damage )
	{
		if (mBlood != "")
		{
			// Создаем кровь
			EntityPtr blood = FactoryManager::GetSingleton()->CreateEntity(mBlood, "");

			// Помещаем кровь на уровень травы
			GetLevel()->GetLayer("Grass")->Add(blood);

			// Устанавливаем позицию крови
			blood->SetPosition(GetActor()->GetPosition().x, GetActor()->GetPosition().y);
			blood->SetAngle(GetActor()->GetAngle());
		}
	}

	void Creature::OnConversationStart( story::SpeakerPtr other )
	{
		StartAction(ActionPtr(new action::SpeakAction()));
	}

	void Creature::OnConversationEnd( story::SpeakerPtr other )
	{
		StopAllActions();
	}

	void Creature::StartConversationWith( story::SpeakerPtr other )
	{
		story::SpeakerPtr me = boost::shared_dynamic_cast<story::ISpeaker>(shared_from_this());
		BehaviourPtr bOtehr = boost::shared_dynamic_cast<Behaviour>(other);
		story::ConversationPtr conversation = GetConversation();
		gcn::ContainerPtr w = boost::shared_dynamic_cast<gcn::Container>(ZombieLand::GetSingleton()->playState->GetGUI()->GetTop());
		gcn::ConversationWindowPtr cw(new gcn::ConversationWindow());
		cw->Init();
		cw->Show(w);
		
		if (GetEntity()->GetName() == "Player")
		{
			cw->SetConversation(conversation, me, other);
		}
		if (bOtehr->GetEntity()->GetName() == "Player")
		{
			cw->SetConversation(conversation, other, me);
		}
	}

};