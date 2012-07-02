#ifndef ISILME_LOGIC_FACTS_H
#define ISILME_LOGIC_FACTS_H

#include "types.h"

namespace logic
{
	/// @class FactBase
	/// Facts table.
	class FactBase
	{
	public:
		typedef std::vector<ValuePtr> ValueVector;
		FactBase(std::string id, int arity);

		void AddFact(ValuePtr a1);

		void AddFact(ValuePtr a1, ValuePtr a2);

		/// Adds a simple fact.
		///
		/// @param [in,out]	values	The values.
		void AddFact(ValueVector& values);

		/// Gets the identifier of the table.
		///
		/// @return	The identifier.
		std::string GetID() const;

		/// Query if table contains a fact about given set of values
		///
		/// @param [in,out]	values	The values.
		///
		/// @return	true if match, false if not.
		bool IsMatch(ValueVector& values) const;
	private:
		typedef std::vector<ValueVector> ValuesTable;

		/// @summary	The identifier of the table.
		std::string mID;

		/// @summary	The arity of the facts.
		int mArity;

		/// @summary	The table of values.
		ValuesTable mTable;
	};
}
#endif