#ifndef ISILME_AI_ATTRIBUTE_H
#define ISILME_AI_ATTRIBUTE_H

#include "Definitions.h"

namespace ai
{
	/// Attribute.
	class ISILME_API Attribute
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

		/// Возвращает максимальное значение атрибута
		/// @return 
		float	GetMaxValue();

		/// Устанавливает максимальное значение атрибута
		void	SetMaxValue(float value);
	private:
		/// The value of the attribute
		float mValue;

		/// Наибольшее возможное значение атрибута
		float mMaxValue;

		/// Наименьшее возможно значение атрибута
		float mMinValue;

		/// The identifier of attribute
		std::string mID;
	};
};

#endif