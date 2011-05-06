#ifndef ZOMBIELAND_ACTION_DIE
#define ZOMBIELAND_ACTION_DIE

#include <Isilme.h>
#include "Definitions.h"
#include <Engine/Action/SpecialAction.h>
#include "ZombieLand/Behaviour/Destroyable.h"

namespace action
{
	class Die : public action::SpecialAction<behaviour::Destroyable>
	{
	public:
		Die();
		virtual ~Die();

		/// Звук проигрываемый при смерти
		void	SetSound(std::string sound);

		/// 
		virtual void	OnDone();

		virtual void	OnStart();

	private:
		HEFFECT mEffect;
	};
};

#endif