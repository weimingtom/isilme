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

#include "stdafx.h"
#include "Context.h"

namespace logic
{
	Context::Context()
	{

	}

	Context::~Context()
	{

	}

	ValuePtr Context::GetParam( std::string id ) const
	{
		ValueMap::const_iterator it = mValues.find(id);
		if (it == mValues.cend())
			return ValuePtr();

		ValuePtr v = it->second.top();
		return v;
	}

	void Context::PushParam( std::string id, ValuePtr value )
	{
		ValueMap::const_iterator it = mValues.find(id);
		if (it == mValues.cend())
			mValues[id] = ValueStack();

		mValues[id].push(value);
	}

	void Context::PopParam(std::string id)
	{
		mValues[id].pop();
		if (mValues[id].size() == 0)
			mValues.erase(id);
	}

}
