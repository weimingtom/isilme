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


#ifndef Isilme_AIPackagesManager_h
#define Isilme_AIPackagesManager_h

#include "AITypes.h"
#include <set>

/// @class AIPackagesManager
/// Handles character's packages, chooses packages
class AIPackagesExecuter
{
public:
    AIPackagesExecuter();
    virtual ~AIPackagesExecuter();
    
    /// Adds a package
    ///
    /// @param package      package to add
    void AddPackage(AIPackagePtr package);
    
    /// Removes a package
    ///
    /// @param package      package to remove
    void RemovePackage(AIPackagePtr package);
    
    /// Chooses an action to execute
    /// @param actor        An actor who will execute an action
    void    ChooseAction(AIBehaviourPtr actor, EntityPtr defaultTarget);
private:
    typedef std::set < AIPackagePtr > PackagesContainer;
    PackagesContainer mPackages;
};

#endif
