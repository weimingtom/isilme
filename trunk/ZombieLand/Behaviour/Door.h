#ifndef GAME_BEHAVIOUR_DOOR_H
#define GAME_BEHAVIOUR_DOOR_H

#include "ZombieLand/Include/Definitions.h"
#include "Activator.h"

namespace behaviour
{
	class DoorDef : public BehaviourDefinition
	{
	public:
		DoorDef();
		virtual ~DoorDef();
		
		virtual BehaviourPtr Create();
		virtual void Parse(TiXmlElement* element);
	private:
	};

	class Door : public Behaviour, public Activator
	{
	public:
		Door();
		virtual ~Door();
		
		virtual bool	IsUsable() const override;

		virtual void	OnUse(CreaturePtr creature) override;

		virtual void	Customize(TiXmlElement* element);
		void Init( DoorDef* def );
	private:
		/// Открыта ли дверь
		bool isOpen;

		/// Сложность вскрытия замка
		int mLock;

		/// Идентификатор двери - точки назначения
		std::string mDoorID;
	};
};

#endif