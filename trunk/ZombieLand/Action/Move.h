#ifndef ZOMBIELAND_ACTION_MOVE_H
#define ZOMBIELAND_ACTION_MOVE_H

#include <Isilme.h>
#include "Definitions.h"

namespace action
{
	class Move : public Action
	{
	public:
		Move();
		virtual ~Move();

		float	GetSpeed();
		void	SetSpeed(float speed);
		void	SetSound(std::string sound);
	protected:
		virtual void OnUpdate(float elapsedTime);
		virtual void OnStart();
		virtual void OnDone();
		virtual void OnForceStop();
	private:
		float mSpeed;
		HEFFECT mSound;
		HCHANNEL mChannel;
	};

	typedef boost::shared_ptr<Move> MovePtr;
};

#endif