#ifndef ZOMBIELAND_ACTION_DIE
#define ZOMBIELAND_ACTION_DIE

#include <Isilme.h>
#include "Definitions.h"
#include "ZombieLand/Behaviour/Destroyable.h"

namespace action
{
	class Die : public Action
	{
	public:
		Die();
		virtual ~Die();

		/// ���� ������������� ��� ������
		void	SetSound(std::string sound);

		/// 
		virtual void	OnDone();

		virtual void	OnStart();

	private:
		HEFFECT mEffect;
	};
};

#endif