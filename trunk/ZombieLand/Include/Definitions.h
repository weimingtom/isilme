#ifndef TT_DEFINITIONS_H
#define TT_DEFINITIONS_H

#include <boost/smart_ptr.hpp>
#include <list>
#include <set>
#include <map>

namespace behaviour
{
	class Bullet;
	typedef boost::shared_ptr<Bullet> BulletPtr;
	
	class Destroyable;
	typedef boost::shared_ptr<Destroyable> DestroyablePtr;

	class Activator;
	typedef boost::shared_ptr<Activator> ActivatorPtr;

	class Creature;
	typedef boost::shared_ptr<Creature> CreaturePtr;

	class Zombie;
	typedef boost::shared_ptr<Zombie> ZombiePtr;

	class Player;
	typedef boost::shared_ptr<Player> PlayerPtr;
};

namespace action
{
	class Move;
	typedef boost::shared_ptr<Move> MovePtr;

	class Die;
	typedef boost::shared_ptr<Die> DiePtr;

	class Shot;
	typedef boost::shared_ptr<Shot> ShotPtr;

	class Attack;
	typedef boost::shared_ptr<Attack> AttackPtr;

	class Heal;
	typedef boost::shared_ptr<Heal> HealPtr;

	class Wind;
	typedef boost::shared_ptr<Wind> WindPtr;

	class Shild;
	typedef boost::shared_ptr<Shild> ShildPtr;
};

namespace state
{
	class Play;
	typedef boost::shared_ptr<Play> PlayPtr;
};

namespace graphics
{
	class Creature;
};

class Item;
typedef boost::shared_ptr<Item> ItemPtr;
typedef std::vector<ItemPtr>	ItemsList;

class Inventory;
typedef boost::shared_ptr<Inventory> InventoryPtr;
typedef boost::weak_ptr<Inventory>	InventoryWPtr;

#endif