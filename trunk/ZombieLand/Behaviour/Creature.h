#ifndef ZOMBIELAND_BEHAVIOUR_CREATURE_H
#define ZOMBIELAND_BEHAVIOUR_CREATURE_H

#include "../Definitions.h"
#include "Destroyable.h"
#include "Container.h"
#include "Activator.h"

namespace behaviour
{
	class CreatureDef : public BehaviourDefinition
	{
	public:
		virtual BehaviourPtr Create();

		virtual void Parse(TiXmlElement* element);

		/// ������ ���������� � ��������
		void	ParseFractions(TiXmlElement* fractionsElement);

		/// ������ ������ ��
		void	ParseAI(TiXmlElement* AIElement);

		float	Energy;
		float	MaxEnergy;
		float	EnergyRestoration;

		luabind::object OnThink;

		std::string Conversation;

		/// Definition of the AI
		AIBehaviourDef AIDef;

		/// Definition of inventory
		ContainerDef containerDef;

		DestroyableDef destroyableDef;
	};

	class Creature : public AIBehaviour, public Destroyable, public story::Speaker/*, public Steerable*/, public Activator, public Container
	{
	public:
		Creature();
		virtual ~Creature();

		/// Initiate behaviour by data
		void Init(CreatureDef* def);

		action::MovePtr GetMoveAction();

		action::MovePtr GetMoveBackAction();

		/// �������� �� ��������� ������
		ActionPtr GetShotAction();

		/// ����������� ��������� ������
		ActionPtr	GetReloadAction();

		/// ������������� �����������
		ActionPtr	GetSpellAction();

		action::AttackPtr GetAttackAction();

		virtual void	OnUpdate(float elapsedTIme);

		void	RotateToPoint(Vector2 position);

		/// ������������� ����� �������
		void	SetEnergy(float energy);

		/// ���������� ����� �������
		float	GetEnergy();

		/// ������������� ������������ ����� �������
		void	SetMaxEnergy(float energy);

		/// ���������� ������������ ����� �������
		float	GetMaxEnergy();

		/// ������������ ������
		void	NextWeapon();

		/// ������������ �����������
		void	NextSpell();

		/// �������� ���������
		void	SwitchActivator();

		/// ��������� ���������� ������
		void	SavePoint();

		/// ������� ������
		void	Respawn();

		void	SetTarget();

		void	ClearTarget();

		EntityPtr GetTarget();
		
		/// ���������� ����� �� ������ ��������� ������
		CreaturePtr GetEnemy(int index);

		/// ���������� ���������� ������
		int GetEnemiesCount();

		/// ���������� true, ���� � ���������� ����� �����������������
		virtual bool IsUsable();

		/// ��������� ������ � ����������
		virtual void	OnUse(CreaturePtr creature);

		virtual void OnDie() override;

		ActionPtr GetDieAction();

		virtual void OnGotDamage(const float damage) override;
	protected:

		void UpdateEnemiesList();
		EntityPtr	mTarget;
		bool	isReloading;

		int		mCurrentWeapon;
		int		mCurrentSpell;
		int pw, ps;
	
		Vector2	mCheckPoint;


		/// ���������
		action::MovePtr	mMoveAction;
		action::MovePtr	mMoveBack;
		
		ActionPtr	mShotAction;
		ActionPtr	mReloadAction;
		ActionPtr	mSpellAction;
		action::AttackPtr mAttack;

		
		/// ������������
		float	mEnergy;
		float	mMaxEnergy;
		float	mEnergyResoration;

		/// ������ �������� 
		/// @depricated
		luabind::object	onThink; // onThink(me, elapsedTime)

		/// ������ ��������� ������
		std::vector<CreaturePtr> mEnemies;

		action::DiePtr	mDieAction;
};

};
#endif