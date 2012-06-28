#ifndef TT_DEFINITIONS_H
#define TT_DEFINITIONS_H

#include <boost/smart_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include <list>
#include <set>
#include <map>
#include <string>

#include <Engine/Isilme.h>

#include "Engine/GUI/ProgressBar.h"
#include "Engine/GUI/HGELabel.h"
#include "Engine/GUI/QuestBook.h"
#include "Engine/Inventory/GUI/InventoryWindow.h"
#include "Engine/GUI/ConversationWindow.h"

#include <Engine/Story/Quests.h>
#include <Engine/Story/Stage.h>
#include <Engine/Story/Story.h>
#include <Engine/Story/Phrase.h>
#include <Engine/Story/Conversation.h>
#include <Engine/Story/Quest.h>
#include <Engine/Story/Speaker.h>

#include <Engine/AI/AI.h>

#include <Engine/Palette/AIPalette.h>

#include <Engine/Inventory/Inventory.h>
#include <Engine/Inventory/Item.h>

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

	class Door;
	typedef boost::shared_ptr<Door> DoorPtr;

	class Item;
	typedef boost::shared_ptr<Item> ItemPtr;
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

	class MoveTo;
	typedef boost::shared_ptr<MoveTo> MoveToPtr;
	typedef boost::weak_ptr<MoveTo> MoveToWPtr;

	class Avoid;
	typedef boost::shared_ptr<Avoid> AvoidPtr;
	typedef boost::weak_ptr<Avoid> AvoidWPtr;
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


class LootRecord;

class LootTable;
typedef boost::shared_ptr<LootTable> LootTablePtr;
typedef std::map<std::string, LootTablePtr> LootMap;

class LootManager;
#endif