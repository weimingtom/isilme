#ifndef ACTION_AVOID_H
#define ACTION_AVOID_H

#include "../Definitions.h"
namespace action
{
	class Avoid : public Action
	{
	public:
		Avoid();
		virtual ~Avoid();

		virtual void	OnStart();
		virtual void	OnDone();
		virtual void	OnForceStop();
		virtual void	OnUpdate(float elapsedTime);
	protected:
		action::MovePtr mAction;
		behaviour::CreaturePtr mCreature;
	};
};

#endif