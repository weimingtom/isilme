#include "ZombieLand.h"

void	ScriptAPI::RegisterAPI()
{
	Lua* lua = Engine::GetSingleton()->GetLua();
	lua->RegisterFunction<bool, std::string, float, GiveHP>("GiveHP");

	//lua->RegisterFunction<std::string, std::string, std::string, CreateEntity>("CreateEntity");
	lua->RegisterFunction<bool, std::string, DestroyEntity>("DestroyEntity");
	//lua->RegisterFunction<bool, GiveRose>("GiveRose");
	//lua->RegisterFunction<bool, std::string, std::string, MoveEntityToLayer>("MoveEntityToLayer");
	//lua->RegisterFunction<bool, std::string, float, float, float, MoveEntityToPosition>("MoveEntityToPosition");
	//lua->RegisterFunction<bool, int, GiveGunAmmo>("GiveGunAmmo");
	//lua->RegisterFunction<bool, int, GiveFireAmmo>("GiveFireAmmo");
	//lua->RegisterFunction<bool, int, GiveForcedAmmo>("GiveForcedAmmo");
	//lua->RegisterFunction<bool, int, GiveRockets>("GiveRockets");
	//lua->RegisterFunction<float, std::string, GetHealth>("GetHealth");
	//lua->RegisterFunction<float, std::string, float, SetHealth>("SetHealth");
	//lua->RegisterFunction<float, std::string, GetEntityX>("GetEntityX");
	//lua->RegisterFunction<float, std::string, GetEntityY>("GetEntityY");
	//lua->RegisterFunction<float, std::string, GetEntityAngle>("GetEntityAngle");
	//lua->RegisterFunction<float, std::string, float, float, Damage>("Damage");
	//lua->RegisterFunction<bool, std::string, float, float, SetEntityVelocity>("SetEntityVelocity");
	//lua->RegisterFunction<bool, std::string, float, float, SetEntityImpulse>("SetEntityImpulse");
	//lua->RegisterFunction<bool, int, AddOrbs>("AddOrbs");
}

bool	ScriptAPI::GiveHP(std::string name, float hp)
{
	try
	{
		EntityPtr entity = FactoryManager::GetSingleton()->GetEntity(name);
		behaviour::DestroyablePtr b = boost::shared_dynamic_cast<behaviour::Destroyable>(entity->GetBehaviour());

		b->SetHealth(b->GetHealth() + hp);
	}
	catch(...)
	{
		return false;
	}
	return true;
}
//
//bool	ScriptAPI::AddOrbs(int count)
//{
//	Entity* player = FactoryManager::GetSingleton()->GetEntity("Player");
//	PlayerBehaviour* behaviour = (PlayerBehaviour*)(player->GetBehaviour());
//
//	behaviour->SetOrbCount(behaviour->GetOrbCount() + count);
//	return true;
//}

bool	ScriptAPI::DestroyEntity(std::string name)
{
	EntityPtr entity = FactoryManager::GetSingleton()->GetEntity(name);
	entity->Remove();
	return true;
}

//bool	ScriptAPI::GiveFireAmmo(int count)
//{
//	Entity* player = FactoryManager::GetSingleton()->GetEntity("Player");
//	PlayerBehaviour* behaviour = (PlayerBehaviour*)(player->GetBehaviour());
//
//	behaviour->GetFireGun()->SetAmmo(behaviour->GetFireGun()->GetAmmo() + count);
//
//	return true;
//
//}
//
//bool	ScriptAPI::GiveForcedAmmo(int count)
//{
//	Entity* player = FactoryManager::GetSingleton()->GetEntity("Player");
//	PlayerBehaviour* behaviour = (PlayerBehaviour*)(player->GetBehaviour());
//
//	behaviour->GetForcedGun()->SetAmmo(behaviour->GetForcedGun()->GetAmmo() + count);
//
//	return true;
//
//}
//
//bool	ScriptAPI::GiveRockets(int count)
//{
//	Entity* player = FactoryManager::GetSingleton()->GetEntity("Player");
//	PlayerBehaviour* behaviour = (PlayerBehaviour*)(player->GetBehaviour());
//
//	behaviour->GetRocketLauncher()->SetAmmo(behaviour->GetRocketLauncher()->GetAmmo() + count);
//
//	return true;
//
//}
//
//bool	ScriptAPI::GiveGunAmmo(int count)
//{
//	Entity* player = FactoryManager::GetSingleton()->GetEntity("Player");
//	PlayerBehaviour* behaviour = (PlayerBehaviour*)(player->GetBehaviour());
//
//	behaviour->GetGun()->SetAmmo(behaviour->GetGun()->GetAmmo() + count);
//
//	return true;
//}
//
//bool	ScriptAPI::GiveRose()
//{
//	// Получить профиль игрока
//	// Добавить розу
//	// Восстановить здоровье
//	return true;
//}
//
//std::string ScriptAPI::CreateEntity(std::string type, std::string name)
//{
//	Level* level = ZombieLand::GetSingleton()->GetStateManager()->GetState()->GetLevel();
//	Entity* entity = FactoryManager::GetSingleton()->CreateEntity(type, name, level);
//
//	return entity->GetName();
//}
//
//bool	ScriptAPI::MoveEntityToLayer(std::string entity, std::string layer)
//{
//	Entity* e = FactoryManager::GetSingleton()->GetEntity(entity);
//	Level* level = e->GetLevel();
//	level->GetLayer(layer)->Add(e);
//
//	return true;
//}
//
//bool	ScriptAPI::MoveEntityToPosition(std::string name, float x, float y, float angle)
//{
//	Entity* entity = FactoryManager::GetSingleton()->GetEntity(name);
//	entity->SetPosition(x, y);
//	entity->SetAngle(angle);
//	return true;
//}
//
//bool	ScriptAPI::SetEntityPosition(std::string name, float x, float y)
//{
//	Entity* entity = FactoryManager::GetSingleton()->GetEntity(name);
//	entity->SetPosition(x, y);
//	return true;
//}
//
//bool	ScriptAPI::SetEntityAngle(std::string name, float angle)
//{
//	Entity* entity = FactoryManager::GetSingleton()->GetEntity(name);
//	entity->SetAngle(angle);
//	return true;
//}
//
//float	ScriptAPI::GetHealth(std::string creature)
//{
//	Entity* entity = FactoryManager::GetSingleton()->GetEntity(creature);
//	DestroyableObject* behaviour = (DestroyableObject*)(entity->GetBehaviour());
//	return behaviour->GetHealth();
//}
//
//float	ScriptAPI::SetHealth(std::string creature, float health)
//{
//	Entity* entity = FactoryManager::GetSingleton()->GetEntity(creature);
//	DestroyableObject* behaviour = (DestroyableObject*)(entity->GetBehaviour());
//
//	behaviour->SetHealth(health);
//	return behaviour->GetHealth();
//}
//
//float	ScriptAPI::GetEntityX(std::string name)
//{
//	Entity* entity = FactoryManager::GetSingleton()->GetEntity(name);
//	return entity->GetPosition().x;
//}
//
//float	ScriptAPI::GetEntityY(std::string name)
//{
//	Entity* entity = FactoryManager::GetSingleton()->GetEntity(name);
//	return entity->GetPosition().y;
//}
//
//float	ScriptAPI::GetEntityAngle(std::string name)
//{
//	Entity* entity = FactoryManager::GetSingleton()->GetEntity(name);
//	return entity->GetAngle();
//}
//
//float	ScriptAPI::Damage(std::string creature, float normalDamage, float fireDamage)
//{
//	Entity* entity = FactoryManager::GetSingleton()->GetEntity(creature);
//	DestroyableObject* behaviour = (DestroyableObject*)(entity->GetBehaviour());
//	
//	::Damage d;
//	d.normalDamage = normalDamage;
//	behaviour->Damage(d);
//	return behaviour->GetHealth();
//}
//
//bool	ScriptAPI::SetEntityVelocity(std::string name, float vx, float vy)
//{
//	Entity* entity = FactoryManager::GetSingleton()->GetEntity(name);
//	entity->GetBody()->SetLinearVelocity(Vector2(vx, vy));
//
//	return true;
//}
//
//bool ScriptAPI::SetEntityImpulse(std::string name, float fx, float fy)
//{
//	Entity* entity = FactoryManager::GetSingleton()->GetEntity(name);
//	if (entity->GetBody()->GetType() == BodyDef::Box2DBody)
//	{
//		Box2DBody* body = (Box2DBody*)(entity->GetBody());
//		body->GetBox2DBody()->ApplyLinearImpulse(Vector2(fx, fy), Vector2(0.0f, 0.0f));
//		return true;
//	}
//
//	return false;
//}