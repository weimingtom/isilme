#ifndef ISILME_AI_ATTRIBUTE_H
#define ISILME_AI_ATTRIBUTE_H

#include "Definitions.h"


/// @class Attribute.
class ISILME_API Attribute
{
public:
	static const float Infinity;
	/// Constructor.
	///
	/// @param	id   	The identifier.
	/// @param	value	The value.
	Attribute(std::string id, float value = 0.0f, float maxValue = Attribute::Infinity);

	/// Destructor.
	virtual ~Attribute();

	/// Gets the value.
	///
	/// @return	The value.
	float	GetValue() const;

	/// Sets a value.
	///
	/// @param	value	The value.
	void	SetValue(float value);

	/// Gets the identifier.
	///
	/// @return	The identifier.
	std::string GetID() const;

	/// Gets maximum attribute value
	/// @return 
	float	GetMaxValue() const;

	/// Sets maximum attribute value
	void	SetMaxValue(float value);
private:
	/// The value of the attribute
	float mValue;

	/// Max value
	float mMaxValue;

	/// Min value
	float mMinValue;

	/// The identifier of attribute
	std::string mID;
};

#endif