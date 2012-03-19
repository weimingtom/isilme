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

		/// Чтение информации о фракциях
		void	ParseFractions(TiXmlElement* fractionsElement);

		/// Чтение пактов ИИ
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

		/// Стрельба из активного оружия
		ActionPtr GetShotAction();

		/// Перезарядка активного оружия
		ActionPtr	GetReloadAction();

		/// Использование способности
		ActionPtr	GetSpellAction();

		action::AttackPtr GetAttackAction();

		virtual void	OnUpdate(float elapsedTIme);

		void	RotateToPoint(Vector2 position);

		/// Устанавливает запас энергии
		void	SetEnergy(float energy);

		/// Возвращает запас энергии
		float	GetEnergy();

		/// Устанавливает максимальный запас энергии
		void	SetMaxEnergy(float energy);

		/// Возвращает максимальный запас энергии
		float	GetMaxEnergy();

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

		/// Возвращает true, если с персонажем можно взаимодействовать
		virtual bool IsUsable();

		/// Запускает диалог с персонажем
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

		action::DiePtr	mDieAction;
};

};
#endif