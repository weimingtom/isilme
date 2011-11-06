#ifndef ZOMBIELAND_BEHAVIOUR_CREATURE_H
#define ZOMBIELAND_BEHAVIOUR_CREATURE_H

#include <Isilme.h>
#include "ZombieLand/Include/Definitions.h"
#include "Destroyable.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include <luabind/luabind.hpp>

namespace behaviour
{
	struct FractionInfo
	{
	public:
		std::string id;
		int	rank;
	};

	class CreatureDef : public DestroyableDef
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
		std::list<FractionInfo> Fractions;
		std::list<std::string> AIPackages;
	};

	class Creature : public Destroyable
	{
	public:
		Creature(CreatureDef* def);
		virtual ~Creature();

		action::MovePtr GetMoveAction();

		action::MovePtr GetMoveBackAction();

		/// �������� �� ��������� ������
		ActionPtr GetShotAction();

		/// ����������� ��������� ������
		ActionPtr	GetReloadAction();

		/// ������������� �����������
		ActionPtr	GetSpellAction();

		action::AttackPtr GetAttackAction();

		virtual void	Think(float elapsedTIme);

		void	RotateToPoint(Vector2 position);

		/// ������������� ����� �������
		void	SetEnergy(float energy);

		/// ���������� ����� �������
		float	GetEnergy();

		/// ������������� ������������ ����� �������
		void	SetMaxEnergy(float energy);

		/// ���������� ������������ ����� �������
		float	GetMaxEnergy();

		/// ���������� ���� �� �������
		int GetRank(FractionPtr fraction);

		/// ���������� ���� �� ������� 
		int GetRank(std::string fractionID);

		/// ������������� ����
		void	SetRank(FractionPtr fraction, int rank);

		/// ������������� ����
		void	SetRank(std::string fractionID, int rank);	

		/// ���������� ��������� � ������� ���������
		int		GetAttitudeTo(CreaturePtr creature);

		ActionPtr mWanderAction;
	protected:

		/// ������� ���������
		std::map<FractionPtr, int>	mFractions;

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
};

};
#endif