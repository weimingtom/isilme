//  Copyright (C) 2010-2012 Alexander Alimov
//
//	This file is part of Isilme SDK.
//
//		Isilme SDK is free software: you can redistribute it and/or modify
//		it under the terms of the GNU Lesser General Public License as published by
//		the Free Software Foundation, either version 3 of the License, or
//		(at your option) any later version.
//
//		Isilme SDK is distributed in the hope that it will be useful,
//		but WITHOUT ANY WARRANTY; without even the implied warranty of
//		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//		GNU Lesser General Public License for more details.
//
//		You should have received a copy of the GNU Lesser General Public License
//		along with Isilme SDK.  If not, see <http://www.gnu.org/licenses/>.
//
//	Этот файл — часть Isilme SDK.
//
//		Isilme SDK - свободная программа: вы можете перераспространять ее и/или
//		изменять ее на условиях Меньшей стандартной общественной лицензии GNU в том виде,
//		в каком она была опубликована Фондом свободного программного обеспечения;
//		либо версии 3 лицензии, либо (по вашему выбору) любой более поздней
//		версии.
//
//		Isilme SDK распространяется в надежде, что она будет полезной,
//		но БЕЗО ВСЯКИХ ГАРАНТИЙ; даже без неявной гарантии ТОВАРНОГО ВИДА
//		или ПРИГОДНОСТИ ДЛЯ ОПРЕДЕЛЕННЫХ ЦЕЛЕЙ. Подробнее см. в Меньшей стандартной
//		общественной лицензии GNU.
//
//		Вы должны были получить копию Меньшей стандартной общественной лицензии GNU
//		вместе с этой программой. Если это не так, см.
//		<http://www.gnu.org/licenses/>.
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