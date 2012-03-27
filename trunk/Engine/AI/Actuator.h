#ifndef ISILME_AI_ACTUATOR_H
#define ISILME_AI_ACTUATOR_H

#include "AITypes.h"

class Actuator
{
public:
	/// Constructor
	///
	/// @param		id	Identifier of the actuator. Should be unique
	Actuator(std::string id);

	/// Gets identifier of the actuator
	std::string	GetID() const;

	/// Gets if the actuator is locked
	bool IsLocked() const;

	/// Makes actuator busy by an action
	///
	/// @param action an action
	/// @param force  true if need to stop current action
	/// 
	/// @return true, if action is locked
	bool LockByAction(ActionPtr action, bool force = false);

	/// Makes actuator free
	/// If actuator is locked
	void Unlock();

	/// Updates actuator state
	void Update(float elapsedTime);
private:
	/// Action that own actuator
	ActionPtr	mOwner;

	/// Identifier
	std::string mID;
};
#endif