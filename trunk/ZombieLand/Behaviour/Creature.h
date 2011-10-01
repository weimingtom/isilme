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
	class CreatureDef : public DestroyableDef
	{
	public:
		virtual BehaviourPtr Create();

		virtual void Parse(TiXmlElement* element);

		float	Energy;
		float	MaxEnergy;
		float	EnergyRestoration;

		luabind::object OnThink;
	};

	class Creature : public Destroyable
	{
	public:
		Creature(CreatureDef* def);
		virtual ~Creature();

		action::MovePtr GetMoveAction();

		action::MovePtr GetMoveBackAction();

		/// Стрельба из активного оружия
		ActionPtr GetShotAction();

		/// Перезарядка активного оружия
		ActionPtr	GetReloadAction();

		/// Использование способности
		ActionPtr	GetSpellAction();

		action::AttackPtr GetAttackAction();

		virtual void	Think(float elapsedTIme);

		void	RotateToPoint(Vector2 position);

		/// Устанавливает запас энергии
		void	SetEnergy(float energy);

		/// Возвращает запас энергии
		float	GetEnergy();

		/// Устанавливает максимальный запас энергии
		void	SetMaxEnergy(float energy);

		/// Возвращает максимальный запас энергии
		float	GetMaxEnergy();

		/// Возвращает снаряжение
		inventory::InventoryPtr	GetInventory();

		/// Возвращает ранг во фракции
		int GetRank(FractionPtr fraction);

		/// Возвращает ранг во фракции 
		int GetRank(std::string fractionID);

		/// Устанавливает ранг
		void	SetRank(FractionPtr fraction, int rank);

		/// Устанавливает ранг
		void	SetRank(std::string fractionID, int rank);	

		/// Возвращает значение атрибута
		float		GetAttribute(Attribute attr);

		/// Устанваливает значение атрибута
		void	SetAttribute(Attribute attr, float value);

		/// Возвращает отношение к другому персонажу
		int		GetAttitudeTo(CreaturePtr creature);
	protected:
		std::map<Attribute, float> mAttributes;
		std::map<FractionPtr, int>	mFractions;
		action::MovePtr	mMoveAction;
		action::MovePtr	mMoveBack;
		ActionPtr	mShotAction;
		ActionPtr	mReloadAction;
		ActionPtr	mSpellAction;
		action::AttackPtr mAttack;

		inventory::InventoryPtr	mInventory;
		

		float	mEnergy;
		float	mMaxEnergy;
		float	mEnergyResoration;

		luabind::object	onThink; // onThink(me, elapsedTime)
	};

};
#endif