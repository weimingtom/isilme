#include "ZombieLand.h"
#include "Shot.h"
#include "ZombieLand/Behaviour/Creature.h"
#include "ZombieLand/Behaviour/Bullet.h"

namespace action
{
	Shot::Shot()
	{
		mEndingTime = 0.2f;
		mSound = 0;
	}

	Shot::~Shot()
	{
	}

	void	Shot::SetSound(std::string sound)
	{
		mSound = Engine::GetSingleton()->GetResourceManager()->GetEffect(sound);
	}

	void	Shot::OnStart()
	{
		if (mSound)
			Engine::GetSingleton()->GetSoundSystem()->PlayEffect(mSound);

		EntityPtr bullet = FactoryManager::GetSingleton()->CreateEntity("Bullet", "", GetLevel());
		bullet->SetAngle(GetActor()->GetAngle());
		bullet->SetPosition(GetActor()->GetPosition().x, GetActor()->GetPosition().y);

		(boost::shared_dynamic_cast<behaviour::Bullet, Behaviour>(bullet->GetBehaviour()))->SetGunslinger(GetActor()->GetBehaviour());
		GetLevel()->GetLayer("Bullets")->Add(bullet);
	}
};