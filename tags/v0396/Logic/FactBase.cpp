#include "stdafx.h"
#include "FactBase.h"

namespace logic
{
	bool IsMatch(const FactBase::ValueVector& v1, const FactBase::ValueVector& v2)
	{
		if (v1.size() != v2.size())
			return false;

		FactBase::ValueVector::const_iterator it1 = v1.cbegin();
		FactBase::ValueVector::const_iterator it2 = v2.cbegin(); 
		while (it1 != v1.cend())	
		{
			if (*it1 != *it2)
				return false;
			++it1;
			++it2;
		}
		return true;
	}
	std::string FactBase::GetID() const
	{
		return mID;
	}

	FactBase::FactBase( std::string id , int arity)
	{
		mID = id;
		mArity = arity;
	}

	void FactBase::AddFact( ValueVector& values )
	{
		mTable.push_back(values);
	}

	void FactBase::AddFact( ValuePtr a1 )
	{
		ValueVector v;
		v.push_back(a1);
		AddFact(v);
	}

	void FactBase::AddFact( ValuePtr a1, ValuePtr a2 )
	{
		ValueVector v;
		v.push_back(a1);
		v.push_back(a2);
		AddFact(v);
	}

	bool FactBase::IsMatch( ValueVector& values ) const
	{
		for (ValuesTable::const_iterator it = mTable.cbegin(); it != mTable.cend(); ++it)
		{
			if (::logic::IsMatch(*it, values))
				return true;
		}
		return false;
	}


}