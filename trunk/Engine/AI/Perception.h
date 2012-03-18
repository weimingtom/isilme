#ifndef ISILME_AI_PERCEPT_H
#define ISILME_AI_PERCEPT_H

#include "AITypes.h"

/// @class Perception
/// 
class ISILME_API Perception
{
public:
	Perception();
	virtual ~Perception();

	/// Gets ID of the perception
	std::string GetID() const;

	/// Sets ID for the perception
	void SetID(std::string id);

	/// Gets value
	virtual float GetValue(BehaviourPtr behaviour) const = 0;
private:
	/// ID of the perception
	std::string mID;
};

class ISILME_API AttributePerception : public Perception
{
public:
	AttributePerception(std::string attribute);

	/// Gets attribute ID
	std::string GetAttributeID() const;

	/// Sets attribute ID
	void SetAttributeID(std::string attr);

	virtual float GetValue(BehaviourPtr behaviour) const override;
private:
	std::string mAttribute;
};

class ISILME_API ScriptedPerception : public Perception
{
public:
	/// Gets function
	luabind::object GetLuaFunction() const;

	/// Sets function
	void SetLuaFunction(luabind::object f);

	virtual float GetValue(BehaviourPtr behaviour) const override;
private:
	luabind::object mLuaFunction;
};

class ISILME_API LogicPerception : public Perception
{

};

#endif