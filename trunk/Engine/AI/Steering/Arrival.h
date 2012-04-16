//  Copyright (C) 2010-2012 VSTU
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
#ifndef ISILME_AI_STEERING_ARRIVAL_H
#define ISILME_AI_STEERING_ARRIVAL_H

#include "SteeringTypes.h"
#include "ISteering.h"

namespace steering
{
	/// @class Arrival
	///
	/// Arrive to point 
	// target_offset = target - position
	// distance = length (target_offset)
	// ramped_speed = max_speed * (distance / slowing_distance)
	// clipped_speed = minimum (ramped_speed, max_speed)
	// desired_velocity = (clipped_speed / distance) * target_offset
	// steering = desired_velocity - velocity
	class Arrival : public ISteering
	{
	public:
		Arrival(VehiclePtr actor, const Vector2& target, float slowDistance);

		virtual Vector2 CalcVelocity() override;
	private:
		/// Actor
		VehiclePtr mActor;

		/// Target
		Vector2 mTarget;

		/// Distance when to slow down
		float mSlowDistance;
	};
}
#endif