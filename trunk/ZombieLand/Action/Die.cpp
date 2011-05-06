#include "ZombieLand.h"
#include "Die.h"

namespace action
{
	Die::Die()
	{
		mDoingTime = 1.0f;
		mEffect = 0;
	}

	Die::~Die()
	{
	}

	void	Die::OnDone()
	{
	}

	void	Die::OnStart()
	{
		GetActor()->RemoveBody();
		GetActor()->GetBehaviour()->SetActive(false);

		if (mEffect != 0)
		Engine::GetSingleton()->GetSoundSystem()->PlayEffect(mEffect);

		//GetLevel()->GetLayer("Grass")->Add(GetActor());
	}

	void	Die::SetSound(std::string sound)
	{
		mEffect = Engine::GetSingleton()->GetResourceManager()->GetEffect(sound);
	}
};