#ifndef ISILME_AI_ATTRIBUTE_H
#define ISILME_AI_ATTRIBUTE_H

#include "Definitions.h"

namespace ai
{
	/// Attribute.
	class IsilmeExport Attribute
	{
	public:
		/// Constructor.
		///
		/// @param	id   	The identifier.
		/// @param	value	The value.
		Attribute(std::string id, float value);

		/// Destructor.
		virtual ~Attribute();

		/// Gets the value.
		///
		/// @return	The value.
		float	GetValue();

		/// Sets a value.
		///
		/// @param	value	The value.
		void	SetValue(float value);

		/// Gets the identifier.
		///
		/// @return	The identifier.
		std::string GetID();
	private:
		///< The value of the attribute
		float mValue;

		///< The identifier of attribute
		std::string mID;
	};
};

#endif