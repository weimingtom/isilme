#include "stdafx.h"
#include "Rule.h"
#include "details/LocalContext.h"

namespace logic
{
	Rule1::Rule1(std::string a1, AtomPtr condition)
	{
		mA1 = "@";
		mA1 += a1;
		mCondition = condition;
	}

	Rule1::~Rule1()
	{

	}

	bool Rule1::Calc( ContextPtr context )
	{
		
		return false;
	}

}