#include "ZombieLand.h"
#include "Activator.h"
#include "Creature.h"
#include <boost/smart_ptr.hpp>
#include <boost/pointer_cast.hpp>

namespace behaviour
{
	Activator::Activator(BehaviourDefinition* def) : Behaviour(def)
	{
		isUsable = true;
	}

	Activator::~Activator()
	{
	}

	void	Activator::UseBy(CreaturePtr creature)
	{
		if (isUsable && IsActive() && !(GetActor()->IsRemoved()))
			OnUse(creature);
	}

	void	Activator::OnUse(CreaturePtr creature)
	{
	}

	void	Activator::SetUsable(bool usable)
	{
		isUsable = usable;
	}

	bool	Activator::IsUsable()
	{
		return isUsable;
	}

	ActivatorPtr	Activator::GetActivatorFor(EntityPtr entity)
	{
		Box2DBody* _body = (Box2DBody*)entity->GetBody();
		b2Body* body = _body->GetBox2DBody();
		b2ContactEdge* edge = body->GetContactList();

		while (edge)
		{
			b2Body* ba = edge->contact->GetFixtureA()->GetBody();
			b2Body* bb = edge->contact->GetFixtureB()->GetBody();

			b2Body* other = ba == body ? bb : ba;
			Entity* e = (Entity*)(other->GetUserData());
			ActivatorPtr a = boost::shared_dynamic_cast<Activator>(e->GetBehaviour());
			if (a != 0)
			{
				if (a->IsUsable())
					return a;
			}
			edge = edge->next;
		}

		return ActivatorPtr();
	}
};