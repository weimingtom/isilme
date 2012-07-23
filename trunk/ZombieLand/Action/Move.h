#ifndef ZOMBIELAND_ACTION_MOVE_H
#define ZOMBIELAND_ACTION_MOVE_H

#include "../include/Definitions.h"

namespace action
{
	class SteeringAction : public Action
	{
	public:
		virtual void OnStart() override;
		virtual void OnUpdate(float elapsedTime) override;
		virtual void OnDone() override;

		VehiclePtr mActorVehicle;
	};

	class Move : public Action
	{
	public:
		Move();
		virtual ~Move();

		void	SetSound(std::string sound);

		/// Возвращает направление движения
		float	GetAngle();

		void	SetAngle(float angle);
	protected:
		virtual void OnUpdate(float elapsedTime);
		virtual void OnStart();
		virtual void OnDone();
		virtual void OnForceStop();
	private:
		float	mAngle;
		float mSpeed;
		HEFFECT mSound;
		HCHANNEL mChannel;
	};

	typedef boost::shared_ptr<Move> MovePtr;
};

#endif