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
#include "Operators.h"
#include "Atom.h"
#include "Context.h"
#include "ValueSet.h"

namespace logic
{
	bool AndOperator::Calc( ContextPtr context )
	{
		return mO1->Calc(context) || mO2->Calc(context);
	}

	AndOperator::AndOperator( AtomPtr o1, AtomPtr o2 )
	{
		mO1 = o1;
		mO2 = o2;
	}

	bool OrOperator::Calc( ContextPtr context )
	{
		return mO1->Calc(context) || mO2->Calc(context);
	}

	OrOperator::OrOperator( AtomPtr o1, AtomPtr o2 )
	{
		mO1 = o1;
		mO2 = o2;
	}

}