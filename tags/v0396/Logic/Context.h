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

#ifndef ISILME_LOGIC_CONTEXT_H
#define ISILME_LOGIC_CONTEXT_H

#include "types.h"

namespace logic
{
	class Context
	{
	public:
		Context();
		virtual ~Context();

		/// Gets a parameter by id
		ValuePtr	GetParam(std::string id) const;

		/// Pushes a parameter into a stack.
		///
		/// @param	id   	The identifier fo the parameter.
		/// @param	value	The value of the parameter.
		void PushParam(std::string id, ValuePtr value);

		/// Pops the parameter from stack by id
		///
		/// @param	id	The identifier.
		void PopParam(std::string id);

		/// Adds a set of facts to the memory.
		///
		/// @param	facts	The facts.
		void AddFacts(FactBasePtr facts);

		/// Gets the table of the facts.
		///
		/// @param	id	The identifier of the table.
		///
		/// @return	The facts table if it exists.
		FactBasePtr	GetFactsTable(std::string id) const;
	private:
		typedef std::stack<ValuePtr> ValueStack;
		typedef std::map<std::string, ValueStack> ValueMap;
		typedef std::map<std::string, FactBasePtr> FactsTable;

		ValueMap mValues;

		/// @summary	The facts.
		FactsTable mFacts;
	};
}
#endif 