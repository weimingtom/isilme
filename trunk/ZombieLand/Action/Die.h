#ifndef ZOMBIELAND_ACTION_DIE
#define ZOMBIELAND_ACTION_DIE

#include "../Definitions.h"
#include "../Behaviour/Destroyable.h"

namespace action
{
	class Die : public Action
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