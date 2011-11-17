#ifndef GAME_BEHAVIOUR_DOOR_H
#define GAME_BEHAVIOUR_DOOR_H

#include "ZombieLand/Include/Definitions.h"
#include "Activator.h"

namespace behaviour
{
	class DoorDef : public ActivatorDef
	{
	public:
		DoorDef();
		virtual ~DoorDef();
		
		virtual BehaviourPtr Create();
		virtual void Parse(TiXmlElement* element);
	private:
	};

	class Door : public Activator
	{
	public:
		Door(DoorDef* def);
		virtual ~Door();
		
		virtual bool	IsUsable();

		virtual void	OnUse(CreaturePtr creature);
	private:
		/// ������� �� �����
		bool isOpen;

		/// ��������� �������� �����
		int mLock;

		/// ������������� ����� - ����� ����������
		std::string mDoorID;
	};
};

#endif