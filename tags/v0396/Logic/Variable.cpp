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
#include "Variable.h"
#include "Context.h"

namespace logic
{
	StackVariable::StackVariable( std::string id )
	{
		mID = id;
	}

	StackVariable::~StackVariable()
	{

	}

	logic::ValuePtr StackVariable::GetValue( ContextPtr context ) const 
	{
		return context->GetParam(mID);
	}

	void StackVariable::SetValue( ContextPtr context, ValuePtr v )
	{

	}


	ValuePtr FreeVariable::GetValue( ContextPtr context )
	{
		return mValue;
	}

	FreeVariable::FreeVariable()
	{

	}

	FreeVariable::~FreeVariable()
	{

	}

	void FreeVariable::SetValue( ContextPtr context, ValuePtr v )
	{

	}

}