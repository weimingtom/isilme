#ifndef ISILME_AI_ATTRIBUTEDEF_H
#define ISILME_AI_ATTRIBUTEDEF_H

#include "AITypes.h"

/// Attribute def.
class AttributeDef
{
public:
	AttributeDef();
	virtual ~AttributeDef();

	/// Parses.
	///
	/// @param [in]	attrElement	If non-null, the attribute element.
	virtual void Parse(TiXmlElement* attrElement);

	/// Creates this object.
	///
	/// @return	.
	virtual AttributePtr Create();
private:
	std::string mID;
	float mValue;
};

#endif