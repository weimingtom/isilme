#ifndef ISILME_LOGIC_FACTATOM_H
#define ISILME_LOGIC_FACTATOM_H

#include "Atom.h"

namespace logic
{
	/// @class FactAtom
	/// Fact atom
	/// Query to simple facts in table
	class FactAtom : public Atom
	{
	public:
		FactAtom(FactBasePtr table, std::string a1);

		FactAtom(FactBasePtr table, ValuePtr value);

		virtual ~FactAtom();

		virtual bool Calc(ContextPtr context);
	private:
		typedef std::vector<std::string> Signature;

		/// @summary	The set of parameters.
		Signature mSignature;

		/// @summary	The table of the facts
		FactBasePtr mTable;

		ValuePtr mValue;
	};
}
#endif