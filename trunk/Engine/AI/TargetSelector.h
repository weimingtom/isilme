//  Copyright (C) 2012 VSTU
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


#ifndef Isilme_TargetSelector_h
#define Isilme_TargetSelector_h

#include "AITypes.h"

/// @class TargetSelector
/// An abstract algorithm to select target
class ISILME_API TargetSelector
{
public:
    virtual ~TargetSelector();
    
    /// Selects target for actor
    ///
    /// @param          actor       Actor who will choose action
    virtual EntityPtr   SelectTargetFor(AIBehaviourPtr behaviour) = 0;
    
    /// Actor
    EntityPtr   actor;
};

/// @class IDTargetSelector
/// Searches an entity with given id
class ISILME_API IDTargetSelector : public TargetSelector
{
public:
    virtual EntityPtr   SelectTargetFor(AIBehaviourPtr behaviour) override;
    
    /// Identifier for searching entity
    std::string ID;
};

/// @class RayCastTargetSelector
/// Selects target in given direction
class ISILME_API RayCastTargetSelector : public TargetSelector
{
public:
    virtual EntityPtr   SelectTargetFor(AIBehaviourPtr behaviour) override;

    /// Direction of the ray
    float       angle;
    
    /// Maximum distance
    float       maxDistance;
};

/// @class PieTargetSelector
/// Selects target in given pie
class ISILME_API PieTargetSelector : public TargetSelector
{
public:
    PieTargetSelector();
    virtual EntityPtr   SelectTargetFor(AIBehaviourPtr behaviour) override;

    float       radius;
    float       directionAngle;
    float       pieAngle;
};

/// @class ParentTaregetSelector
/// Selects target of parent action
class ISILME_API ParentTargetSelector : public TargetSelector
{
    virtual EntityPtr   SelectTargetFor(AIBehaviourPtr behaviour) override;

};
#endif
