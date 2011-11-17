#include "ZombieLand.h"
#include "Door.h"
#include "Creature.h"

namespace behaviour
{
	Door::Door(DoorDef* def) : Activator(def)
	{
	}

	Door::~Door()
	{
	}

	void Door::OnUse(CreaturePtr c)
	{
		EntityPtr destination = FactoryManager::GetSingleton()->GetEntity(mDoorID);
		if (destination)
		{
			destination->GetLayer()->Add(c->GetActor());
			c->GetActor()->SetPosition(destination->GetPosition());
			c->GetActor()->SetAngle(destination->GetAngle());
		}
	}

	bool Door::IsUsable()
	{
		return true;
	}

	DoorDef::DoorDef()
	{
	}

	DoorDef::~DoorDef()
	{
	}


	void DoorDef::Parse(TiXmlElement* element)
	{
		ActivatorDef::Parse(element);
	}

	BehaviourPtr DoorDef::Create()
	{
		return DoorPtr(new Door(this));
	}



};