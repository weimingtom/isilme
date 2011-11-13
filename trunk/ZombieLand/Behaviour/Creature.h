#ifndef ZOMBIELAND_BEHAVIOUR_CREATURE_H
#define ZOMBIELAND_BEHAVIOUR_CREATURE_H

#include <Isilme.h>
#include "ZombieLand/Include/Definitions.h"
#include "Destroyable.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Quest/Conversation.h"
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

		/// Чтение информации о фракциях
		void	ParseFractions(TiXmlElement* fractionsElement);

		/// Чтение пактов ИИ
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

		/// Возвращает ранг во фракции
		int GetRank(FractionPtr fraction);

		/// Возвращает ранг во фракции 
		int GetRank(std::string fractionID);

		/// Устанавливает ранг
		void	SetRank(FractionPtr fraction, int rank);

		/// Устанавливает ранг
		void	SetRank(std::string fractionID, int rank);	

		/// Возвращает отношение к другому персонажу
		int		GetAttitudeTo(CreaturePtr creature);

		/// Переключение оружия
		void	NextWeapon();

		/// Переключение способности
		void	NextSpell();

		/// Включить активатор
		void	SwitchActivator();

		/// Сохранить координаты игрока
		void	SavePoint();

		/// Оживить игрока
		void	Respawn();

		void	SetTarget();
		void	ClearTarget();

		EntityPtr GetTarget();
		
		/// Возвращает врага из списка ближайших врагов
		CreaturePtr GetEnemy(int index);

		/// Возвращает количество врагов
		int GetEnemiesCount();
	protected:
		/// Диалог с персонажем
		story::ConversationPtr mConversation;

		void UpdateEnemiesList();
		EntityPtr	mTarget;
		bool	isReloading;

		int		mCurrentWeapon;
		int		mCurrentSpell;
		int pw, ps;
	
		Vector2	mCheckPoint;

		/// Фракции персонажа
		std::map<FractionPtr, int>	mFractions;

		/// Состояния
		action::MovePtr	mMoveAction;
		action::MovePtr	mMoveBack;
		
		ActionPtr	mShotAction;
		ActionPtr	mReloadAction;
		ActionPtr	mSpellAction;
		action::AttackPtr mAttack;

		
		/// Характеристи
		float	mEnergy;
		float	mMaxEnergy;
		float	mEnergyResoration;

		/// Скрипт итерации 
		/// @depricated
		luabind::object	onThink; // onThink(me, elapsedTime)

		/// Список ближайших врагов
		std::vector<CreaturePtr> mEnemies;
};

};
#endif