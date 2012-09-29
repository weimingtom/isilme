////  Copyright (C) 2010-2012 Alexander Alimov
////
////	This file is part of Isilme SDK.
////
////		Isilme SDK is free software: you can redistribute it and/or modify
////		it under the terms of the GNU Lesser General Public License as published by
////		the Free Software Foundation, either version 3 of the License, or
////		(at your option) any later version.
////
////		Isilme SDK is distributed in the hope that it will be useful,
////		but WITHOUT ANY WARRANTY; without even the implied warranty of
////		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
////		GNU Lesser General Public License for more details.
////
////		You should have received a copy of the GNU Lesser General Public License
////		along with Isilme SDK.  If not, see <http://www.gnu.org/licenses/>.
////
//#include "Logic.h"
//
//namespace logic
//{
//	template <typename TD, typename TB> 
//	boost::shared_ptr<TD> Cast(boost::shared_ptr<TB> value)
//	{
//		return boost::shared_dynamic_cast<TD, TB>(value);
//	}
//
//	class ConstAtom : public Atom
//	{
//	public:
//		ConstAtom(bool value);
//		virtual ~ConstAtom();
//
//		virtual bool Calc(ContextPtr context) override;
//	private:
//		bool mValue;
//	};
//
//	class BoolValue : public Value
//	{
//	public:
//		BoolValue(bool value);
//		virtual ~BoolValue();
//
//		bool GetValue() const;
//	private:
//		bool mValue;
//	};
//	typedef boost::shared_ptr<BoolValue> BoolValuePtr;
//
//	BoolValue::BoolValue( bool value )
//	{
//		mValue = value;
//	}
//
//	BoolValue::~BoolValue()
//	{
//
//	}
//
//	bool BoolValue::GetValue() const
//	{
//		return mValue;
//	}
//
//	bool ConstAtom::Calc( ContextPtr context )
//	{
//		return mValue;
//	}
//
//	ConstAtom::ConstAtom( bool value )
//	{
//		mValue = value;
//	}
//
//	ConstAtom::~ConstAtom()
//	{
//
//	}
//
//	class BoolAtom : public Atom
//	{
//	public:
//		BoolAtom(std::string a1);
//		virtual ~BoolAtom();
//
//		virtual bool Calc(ContextPtr context) override;
//	private:
//		std::string mID;
//	};
//
//	BoolAtom::BoolAtom( std::string a1 )
//	{
//		mID = a1;
//	}
//
//	BoolAtom::~BoolAtom()
//	{
//
//	}
//
//	bool BoolAtom::Calc( ContextPtr context )
//	{
//		ValuePtr v = context->GetParam(mID);
//		BoolValuePtr bv = Cast<BoolValue>(v);
//
//		return bv->GetValue();
//	}
//
//	////////////////////
//	class ActorValue : public Value
//	{
//	public:
//		ActorValue(float x, float y, float health, float mhealth, float alignment);
//		virtual ~ActorValue();
//
//		float mHealth;
//		float mMaxHealth;
//		float mX;
//		float my;
//		float mAlignment;
//	};
//	typedef boost::shared_ptr<ActorValue> ActorValuePtr;
//
//	ActorValue::ActorValue( float x, float y, float health, float mhealth, float alignment )
//	{
//		mX = x;
//		my = y;
//		mHealth = health;
//		mMaxHealth = mhealth;
//		mAlignment = alignment;
//	}
//
//	ActorValue::~ActorValue()
//	{
//
//	}
//
//	//////////
//	class IsWeak : public Atom
//	{
//	public:
//		IsWeak(std::string a1);
//
//		virtual bool Calc(ContextPtr context) override;
//	private:
//		std::string mA1;
//	};
//
//	IsWeak::IsWeak( std::string a1 )
//	{
//		mA1 = a1;
//	}
//
//	bool IsWeak::Calc( ContextPtr context )
//	{
//		ActorValuePtr v = Cast<ActorValue>(context->GetParam(mA1));
//		return v->mHealth < 0.5 * v->mMaxHealth;
//	}
//}
//
//int main()
//{
//	using namespace logic;
//	// Context
//	ContextPtr context(new Context());
//
//	// Set of boolean values
//	ValueSetPtr booleanSet(new ValueSet());
//	booleanSet->AddValue(ValuePtr(new BoolValue(true)));
//	booleanSet->AddValue(ValuePtr(new BoolValue(false)));
//
//	// Set of actor values;
//	ValueSetPtr entitySet(new ValueSet());
//
//	ValuePtr a(new ActorValue(0, 0, 20, 100, 0));
//	ValuePtr b(new ActorValue(5, 0, 60, 100, 2));
//	ValuePtr c(new ActorValue(5, 5, 40, 100, 2));
//	ValuePtr d(new ActorValue(0, 5, 80, 100, 2));
//	ValuePtr e(new ActorValue(2, 1, 60, 100, 2));
//	ValuePtr f(new ActorValue(3, 4, 10, 100, 2));
//
//	entitySet->AddValue(a);
//	entitySet->AddValue(b);
//	entitySet->AddValue(c);
//	entitySet->AddValue(d);
//	entitySet->AddValue(e);
//	entitySet->AddValue(f);
//
//	context->PushParam("a", a);
//	context->PushParam("b", b);
//	context->PushParam("c", c);
//	context->PushParam("d", d);
//	context->PushParam("e", e);
//	context->PushParam("f", f);
//
//	// Test 
//	AtomPtr test1(new ExtQuntifier(
//		"X", 
//		booleanSet, 
//		AtomPtr(new BoolAtom("X"))));
//
//	AtomPtr test2(new AnyQuantifier(
//		"X", 
//		booleanSet, 
//		AtomPtr(new BoolAtom("X"))));
//
//	AtomPtr test3(new IsWeak("a"));
//
//	AtomPtr test4(new IsWeak("b"));
//
//	bool result1 = test1->Calc(context);
//	bool result2 = test2->Calc(context);
//	bool result3 = test3->Calc(context);
//	bool result4 = test4->Calc(context);
//
//	// Test for fact tables
//	FactBasePtr isHuman(new FactBase("isHuman", 1));
//	isHuman->AddFact(a);
//	isHuman->AddFact(b);
//	isHuman->AddFact(c);
//	isHuman->AddFact(d);
//	isHuman->AddFact(e);
//	//isHuman->AddFact(f);
//
//	AtomPtr test5(new AnyQuantifier(
//		"X",
//		entitySet,
//		AtomPtr(new FactAtom(isHuman, "X"))));
//
//	AtomPtr test6(new ExtQuntifier(
//		"X",
//		entitySet,
//		AtomPtr(new FactAtom(isHuman, "X"))));
//
//	AtomPtr test7(new FactAtom(isHuman, a));
//	AtomPtr test8(new FactAtom(isHuman, f));
//
//	bool result5 = test5->Calc(context);
//	bool result6 = test6->Calc(context);
//	bool result7 = test7->Calc(context);
//	bool result8 = test8->Calc(context);
//
//	return 0;
//}
//
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <exception>
#include <iterator>
#include <sstream>
#include <list>

#include <boost/spirit.hpp>
#include <boost/shared_ptr.hpp>

using namespace std;
using namespace boost::spirit;
using namespace boost;

void g(unsigned int i)
{   
	cout << "row: " << i << endl;
}

struct u
{
	u(const char* c): s(c) {}
	void operator()(const char* first, const char* last) const
	{
		cout << s << ": " << string(first, last) << endl;   
	}
private:
	string s;
};


struct Exp
{
};

struct Range: public Exp
{
};

struct Index: public Exp
{
};

struct String: public Exp
{
};

struct Op
{
	virtual ~Op() = 0;
	virtual string name() = 0;
};

Op::~Op() {}

struct CountIf: public Op
{
	string name() { return "CountIf"; }
};

struct Sum: public Op
{
	string name() { return "Sum"; }
};

struct Statement
{
	virtual ~Statement() = 0;
	virtual void print() = 0;
};

Statement::~Statement() {}

struct Formula: public Statement
{
	Formula(const char* first, const char* last): s(first, last), op(new CountIf)
	{
		typedef rule<phrase_scanner_t> r_t;

		r_t r_b_op		= as_lower_d["+"] | as_lower_d["-"];// | "*"  | "/";
	//	r_t r_u_op		= "!";
		r_t r_index     = (+alpha_p)[u("col")] >> uint_p[&g];
		r_t r_range     = r_index >> ':' >> r_index;
		r_t r_string    = ch_p('\"') >> *alnum_p >> '\"';
		r_t r_term		= r_range | r_index | r_string;
		r_t r_exp       = r_term | r_exp >> r_b_op >> r_exp; // will invoke actions for index twice due to range
		r_t r_list      = !(r_exp[u("arg")] % ',');
		r_t r_op        = as_lower_d["countif"] | as_lower_d["sum"];
		r_t r_formula   = r_op >> '(' >> r_list >> ')';

		cout << s << ": matched: " << boolalpha << parse(s.c_str(), r_formula, space_p).full << endl; 
	}
	void print() { cout << "Formula: " << s << " / " << op->name() << endl; }
private:
	string s;
	boost::shared_ptr<Op> op;
	list<boost::shared_ptr<Exp> > exp_list;
};

struct Comment: public Statement
{
	Comment(const char* first, const char* last): comment(first, last) {}
	void print() {cout << "Comment: " << comment << endl; }
private:
	string comment;
};


struct MakeFormula
{
	MakeFormula(list<boost::shared_ptr<Statement> >& list_): list(list_) {}
	void operator()(const char* first, const char* last) const
	{
		cout << "MakeFormula: " << string(first, last) << endl;
		list.push_back(boost::shared_ptr<Statement>(new Formula(first, last)));
	}
private:
	list<boost::shared_ptr<Statement> >& list;
};

struct MakeComment
{
	MakeComment(list<boost::shared_ptr<Statement> >& list_): list(list_) {}
	void operator()(const char* first, const char* last) const
	{
		cout << "MakeComment: " << string(first, last) << endl;
		list.push_back(boost::shared_ptr<Statement>(new Comment(first, last)));
	}
private:
	list<boost::shared_ptr<Statement> >& list;
};


int main(int argc, char* argv[])
{
	try
{
	//typedef vector<string> v_t;
	//v_t v(argv + 1, argv + argc);
	// copy(v.begin(), v.end(), ostream_iterator<v_t::value_type>(cout, "\n"));

	string s;
	getline(cin, s);

	//        =COUNTIF(J2:J36, "Abc")

	typedef list<boost::shared_ptr<Statement> > list_t;
	list_t list;

	typedef rule<phrase_scanner_t> r_t;

	r_t r_index     = (+alpha_p)[u("col")] >> uint_p[&g];
	r_t r_range     = r_index >> ':' >> r_index;
	r_t r_string    = ch_p('\"') >> *alnum_p >> '\"';
	r_t r_exp       = r_range | r_index | r_string; // will invoke actions for index twice due to range
	r_t r_list      = !(r_exp[u("arg")] % ',');
	r_t r_op        = as_lower_d["countif"] | as_lower_d["sum"];
	r_t r_formula   = r_op >> '(' >> r_list >> ')';
	r_t r_statement = (ch_p('=')  >> r_formula   [MakeFormula(list)])
		| (ch_p('\'') >> (*anychar_p)[MakeComment(list)])
		;

	cout << s << ": matched: " << boolalpha << parse(s.c_str(), r_statement, space_p).full << endl; 

	for (list_t::const_iterator it = list.begin(); it != list.end(); ++it)
	{
		(*it)->print();
	}
}
catch(const std::exception& ex)
{
	cerr << "Error: " << ex.what() << endl;
}
}