#include "ZombieLand.h"
#include "Door.h"
#include "Creature.h"

namespace behaviour
{
	Door::Door()
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

	bool Door::IsUsable() const
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
	}

	BehaviourPtr DoorDef::Create()
	{
		DoorPtr d(new Door());
		d->Init(this);
		return  d;
	}


	void Door::Customize(TiXmlElement* element)
	{
		const char* destAttr = element->Attribute("Destination");
		if (destAttr)
			mDoorID = destAttr;
	}

	void Door::Init( behaviour::DoorDef* def )
	{
	}

};