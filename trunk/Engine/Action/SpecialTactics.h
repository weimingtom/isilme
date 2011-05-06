#ifndef ISILME_ACTION_SPECIALTACTICS_H
#define ISILME_ACTION_SPECIALTACTICS_H

#include "Definitions.h"
#include "Tactics.h"

namespace action
{
	template <class T>
	class SpecialTactics : public Tactics
	{
	public:
		virtual ~SpecialTactics()
		{
		}

		T*	GetBehaviour()
		{
			return dynamic_cast<T*>(mBehaviour.lock().get());
		}
	};
};

#endif 