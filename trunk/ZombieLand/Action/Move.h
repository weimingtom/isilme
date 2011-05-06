#ifndef ZOMBIELAND_ACTION_MOVE_H
#define ZOMBIELAND_ACTION_MOVE_H

#include <Isilme.h>
#include "Definitions.h"
#include <Engine/Action/SpecialTactics.h>

namespace action
{
	class Move : public SpecialTactics<behaviour::Creature>
	{
	public:
		Move();
		virtual ~Move();

		float	GetSpeed();
		void	SetSpeed(float speed);
		void	SetSound(std::string sound);
	protected:
		virtual void OnThink(float elapsedTime);
		virtual void OnStart();
		virtual void OnDone();
	private:
		float mSpeed;
		HEFFECT mSound;
		HCHANNEL mChannel;
	};

	typedef boost::shared_ptr<Move> MovePtr;
};

#endif