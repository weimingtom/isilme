#include "IsilmePCH.h"
#include "ObstacleAvoidance.h"
#include "ISteerable.h"

namespace steering
{


	ObstacleAvoidance::ObstacleAvoidance( VehiclePtr actor ) :
		mActor(actor)
	{

	}

	Vector2 ObstacleAvoidance::CalcVelocity()
	{
		Vector2 leftRay = mActor->GetVelocity();
		Vector2 rightRay = mActor->GetVelocity();

		// We have a second to avoid obstacle
		float distance = mActor->GetVelocity().Length() * 1.0f;

		VehiclePtr leftObstacle = mActor->RayQuery(leftRay, distance);
		VehiclePtr rightObstacle = mActor->RayQuery(rightRay, distance);

		if (leftObstacle && rightObstacle)
		{
			// We have 2 obstacles and should ovoid both of them
			Vector2 lAvoidance = CalcVelocity(leftObstacle);
			Vector2 rAvoidance = CalcVelocity(rightObstacle);
			float lSDistance = (leftObstacle->GetPosition() - mActor->GetPosition()).LengthSquared();
			float rSDistance = (rightObstacle->GetPosition() - mActor->GetPosition()).LengthSquared();
			float k = lSDistance / rSDistance;
			Vector2 result = k * lAvoidance + (1.0f - k) * rAvoidance;

			return result;
		}
		else if (leftObstacle)
		{
			// We have only left obstacle
			return CalcVelocity(leftObstacle);
		}
		else if (rightObstacle)
		{
			// We have only right obstacle
			return CalcVelocity(rightObstacle);
		}
		else
		{
			// We have no obstacles
			return Vector2(0.0f, 0.0f);
		}
	}

	Vector2 ObstacleAvoidance::CalcVelocity( VehiclePtr obstacle )
	{
		return Vector2(0.0f, 0.0f);
	}

}