#include "stdafx.h"
#include "FactAtom.h"
#include "FactBase.h"
#include "Context.h"

namespace logic
{


	FactAtom::FactAtom( FactBasePtr table, std::string a1 )
	{
		mTable = table;
		mSignature.push_back(a1);
	}

	FactAtom::FactAtom( FactBasePtr table, ValuePtr value )
	{
		mTable = table;
		mValue = value;
	}

	FactAtom::~FactAtom()
	{

	}

	bool FactAtom::Calc( ContextPtr context )
	{
		FactBase::ValueVector v;

		if (mValue != nullptr)
		{
			v.push_back(mValue);
		}
		else
		{
			for (Signature::iterator it = mSignature.begin(); it != mSignature.end(); ++it)
			{
				v.push_back(context->GetParam(*it));
			}
		}
		return mTable->IsMatch(v);
	}

}