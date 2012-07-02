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
#ifndef ISILME_LOGIC_TYPES_H
#define ISILME_LOGIC_TYPES_H

#include <boost/smart_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <stack>
#include <set>

namespace logic
{
	class Atom;
	typedef boost::shared_ptr<Atom> AtomPtr;

	class Context;
	typedef boost::shared_ptr<Context> ContextPtr;

	class Interpreter;

	class FactBase;
	typedef boost::shared_ptr<FactBase> FactBasePtr;

	class RuleTable;
	typedef boost::shared_ptr<RuleTable> RuleTablePtr;

	class Variable;
	typedef boost::shared_ptr<Variable> VariablePtr;

	class Value;
	typedef boost::shared_ptr<Value> ValuePtr;

	class ValueSet;
	typedef boost::shared_ptr<ValueSet> ValueSetPtr;
}
#endif