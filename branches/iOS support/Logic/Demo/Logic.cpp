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
#include "Logic.h"

namespace logic
{
	template <typename TD, typename TB> 
	boost::shared_ptr<TD> Cast(boost::shared_ptr<TB> value)
	{
		return boost::shared_dynamic_cast<TD, TB>(value);
	}

	class ConstAtom : public Atom
	{
	public:
		ConstAtom(bool value);
		virtual ~ConstAtom();

		virtual bool Calc(ContextPtr context) override;
	private:
		bool mValue;
	};

	class BoolValue : public Value
	{
	public:
		BoolValue(bool value);
		virtual ~BoolValue();

		bool GetValue() const;
	private:
		bool mValue;
	};
	typedef boost::shared_ptr<BoolValue> BoolValuePtr;

	BoolValue::BoolValue( bool value )
	{
		mValue = value;
	}

	BoolValue::~BoolValue()
	{

	}

	bool BoolValue::GetValue() const
	{
		return mValue;
	}

	bool ConstAtom::Calc( ContextPtr context )
	{
		return mValue;
	}

	ConstAtom::ConstAtom( bool value )
	{
		mValue = value;
	}

	ConstAtom::~ConstAtom()
	{

	}

	class BoolAtom : public Atom
	{
	public:
		BoolAtom(std::string a1);
		virtual ~BoolAtom();

		virtual bool Calc(ContextPtr context) override;
	private:
		std::string mID;
	};

	BoolAtom::BoolAtom( std::string a1 )
	{
		mID = a1;
	}

	BoolAtom::~BoolAtom()
	{

	}

	bool BoolAtom::Calc( ContextPtr context )
	{
		ValuePtr v = context->GetParam(mID);
		BoolValuePtr bv = Cast<BoolValue>(v);

		return bv->GetValue();
	}

	////////////////////
	class ActorValue : public Value
	{
	public:
		ActorValue(float x, float y, float health, float mhealth, float alignment);
		virtual ~ActorValue();

		float mHealth;
		float mMaxHealth;
		float mX;
		float my;
		float mAlignment;
	};
	typedef boost::shared_ptr<ActorValue> ActorValuePtr;

	ActorValue::ActorValue( float x, float y, float health, float mhealth, float alignment )
	{
		mX = x;
		my = y;
		mHealth = health;
		mMaxHealth = mhealth;
		mAlignment = alignment;
	}

	ActorValue::~ActorValue()
	{

	}

	//////////
	class IsWeak : public Atom
	{
	public:
		IsWeak(std::string a1);

		virtual bool Calc(ContextPtr context) override;
	private:
		std::string mA1;
	};

	IsWeak::IsWeak( std::string a1 )
	{
		mA1 = a1;
	}

	bool IsWeak::Calc( ContextPtr context )
	{
		ActorValuePtr v = Cast<ActorValue>(context->GetParam(mA1));
		return v->mHealth < 0.5 * v->mMaxHealth;
	}
}

int main()
{
	using namespace logic;
	// Context
	ContextPtr context(new Context());

	// Set of boolean values
	ValueSetPtr booleanSet(new ValueSet());
	booleanSet->AddValue(ValuePtr(new BoolValue(true)));
	booleanSet->AddValue(ValuePtr(new BoolValue(false)));

	// Set of actor values;
	ValueSetPtr entitySet(new ValueSet());

	ValuePtr a(new ActorValue(0, 0, 20, 100, 0));
	ValuePtr b(new ActorValue(5, 0, 60, 100, 2));
	ValuePtr c(new ActorValue(5, 5, 40, 100, 2));
	ValuePtr d(new ActorValue(0, 5, 80, 100, 2));
	ValuePtr e(new ActorValue(2, 1, 60, 100, 2));
	ValuePtr f(new ActorValue(3, 4, 10, 100, 2));

	entitySet->AddValue(a);
	entitySet->AddValue(b);
	entitySet->AddValue(c);
	entitySet->AddValue(d);
	entitySet->AddValue(e);
	entitySet->AddValue(f);

	context->PushParam("a", a);
	context->PushParam("b", b);
	context->PushParam("c", c);
	context->PushParam("d", d);
	context->PushParam("e", e);
	context->PushParam("f", f);

	// Test 
	AtomPtr test1(new ExtQuntifier(
		"X", 
		booleanSet, 
		AtomPtr(new BoolAtom("X"))));

	AtomPtr test2(new AnyQuantifier(
		"X", 
		booleanSet, 
		AtomPtr(new BoolAtom("X"))));

	AtomPtr test3(new IsWeak("a"));

	AtomPtr test4(new IsWeak("b"));

	bool result1 = test1->Calc(context);
	bool result2 = test2->Calc(context);
	bool result3 = test3->Calc(context);
	bool result4 = test4->Calc(context);

	// Test for fact tables
	FactBasePtr isHuman(new FactBase("isHuman", 1));
	isHuman->AddFact(a);
	isHuman->AddFact(b);
	isHuman->AddFact(c);
	isHuman->AddFact(d);
	isHuman->AddFact(e);
	//isHuman->AddFact(f);

	AtomPtr test5(new AnyQuantifier(
		"X",
		entitySet,
		AtomPtr(new FactAtom(isHuman, "X"))));

	AtomPtr test6(new ExtQuntifier(
		"X",
		entitySet,
		AtomPtr(new FactAtom(isHuman, "X"))));

	AtomPtr test7(new FactAtom(isHuman, a));
	AtomPtr test8(new FactAtom(isHuman, f));

	bool result5 = test5->Calc(context);
	bool result6 = test6->Calc(context);
	bool result7 = test7->Calc(context);
	bool result8 = test8->Calc(context);

	return 0;
}

