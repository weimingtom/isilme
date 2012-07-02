#ifndef ISILME_LOGIC_RULETABLE_H
#define ISILME_LOGIC_RULETABLE_H

#include "types.h"

namespace logic
{
	/// @class RuleTable
	/// Table of the rules
	class RuleTable
	{
	public:
		RuleTable(std::string id, int arity);
		virtual ~RuleTable();

		void AddCondtion(std::string a1, AtomPtr conditition);
	private:
		struct Rule
		{
			std::string a1;
			AtomPtr condition;
		};
		typedef std::vector<Rule> CondtionsList;

		/// @summary	The condition.
		CondtionsList mCondition;

		/// @summary	The identifier.
		std::string mID;

		/// @summary	The arity.
		int mArity;

	};
}
#endif