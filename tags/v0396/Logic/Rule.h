#ifndef ISILME_LOGIC_RULE_H
#define ISILME_LOGIC_RULE_H

#include "Atom.h"

namespace logic
{
	class Rule1 : public Atom
	{
	public:
		Rule1(std::string id);
		void AddCondition(AtomPtr);
		virtual ~Rule1();

		virtual bool Calc(ContextPtr context) override;

		VariablePtr GetParam1() const;
	private:
		std::string mID;
		AtomPtr mCondition;
	};

	typedef boost::shared_ptr<Rule1> Rule1Ptr;
}

#endif