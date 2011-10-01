#include "ZombieLand.h"
#include "Wander.h"
#include "MoveTo.h"
#include "Move.h"
#include "ZombieLand/Behaviour/Creature.h"

namespace action
{
	Wander::Wander()
	{
	}

	Wander::~Wander()
	{
	}

	bool	Wander::DoneCondition()
	{
		return false;
	}

	void	Wander::OnStart()
	{
	}

	void	Wander::OnUpdate(float elapsedTime)
	{
	}

	void	Wander::OnDone()
	{
	}

	void	Wander::OnForceStop()
	{
	}
};