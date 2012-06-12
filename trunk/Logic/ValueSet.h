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

#ifndef ISILME_LOGIC_VALUESET_H
#define ISILME_LOGIC_VALUESET_H

#include "types.h"

namespace logic
{
	class Value
	{
	public:
		virtual ~Value() {};
	};

	class ValueSet
	{
		typedef std::vector<ValuePtr> ValueVector;
	public:
		typedef ValueVector::iterator Iterator;

		Iterator	Begin();
		Iterator	End();

		void AddValue(ValuePtr value);

		unsigned int Size() const;
	private:
		ValueVector mValues;
	};

	class NamedSet
	{
		typedef std::map<std::string, ValuePtr> ValueMap;
	public:
		typedef ValueMap::iterator Iterator;

		void AddValue(std::string key, ValuePtr value);

		Iterator	Begin();
		Iterator	End();

		unsigned int Size() const;

		ValuePtr Get(std::string key) const;
	private:
		ValueMap mValues;
	};

	class OrderedSet
	{
		typedef std::vector<ValuePtr> ValueVector;
	public:
	};
}

#endif