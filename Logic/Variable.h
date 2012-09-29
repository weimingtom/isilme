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
#ifndef ISILME_LOGIC_VARIABLE_H
#define ISILME_LOGIC_VARIABLE_H

#include "types.h"

namespace logic
{
	/// @class Variable
	/// Local variable for rules
	class Variable
	{
	public:
		Variable() {};
		virtual ~Variable() {};

		virtual ValuePtr	GetValue(ContextPtr context) const = 0;

		virtual void		SetValue(ContextPtr context, ValuePtr v) = 0;
	private:
	};

	class StackVariable : public Variable
	{
	public:
		StackVariable(std::string id);
		virtual ~StackVariable();
		ValuePtr	GetValue(ContextPtr context) const override;

		void		SetValue(ContextPtr context, ValuePtr v) override;
	private:
		std::string mID;
	};

	class FreeVariable : public Variable
	{
	public:
		FreeVariable();
		virtual ~FreeVariable();

		virtual ValuePtr GetValue(ContextPtr context) ;

		virtual void SetValue(ContextPtr context, ValuePtr v) override;
	private:
		ValuePtr mValue;
	};
}

#endif