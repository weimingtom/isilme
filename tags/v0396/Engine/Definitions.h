//  Copyright (C) 2010-2012 VSTU
//
//	This file is part of Isilme SDK.
//
//		Isilme SDK is free software: you can redistribute it and/or modify
//		it under the terms of the GNU Lesser General Public License as published by
//		the Free Software Foundation, either version 3 of the License, or
//		(at your option) any later version.
//
//		Isilme SDK is distributed in the hope that it will be useful,
//		but WITHOUT ANY WARRANTY; without even the implied warranty of
//		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//		GNU Lesser General Public License for more details.
//
//		You should have received a copy of the GNU Lesser General Public License
//		along with Isilme SDK.  If not, see <http://www.gnu.org/licenses/>.
//
//	Этот файл — часть Isilme SDK.
//
//		Isilme SDK - свободная программа: вы можете перераспространять ее и/или
//		изменять ее на условиях Меньшей стандартной общественной лицензии GNU в том виде,
//		в каком она была опубликована Фондом свободного программного обеспечения;
//		либо версии 3 лицензии, либо (по вашему выбору) любой более поздней
//		версии.
//
//		Isilme SDK распространяется в надежде, что она будет полезной,
//		но БЕЗО ВСЯКИХ ГАРАНТИЙ; даже без неявной гарантии ТОВАРНОГО ВИДА
//		или ПРИГОДНОСТИ ДЛЯ ОПРЕДЕЛЕННЫХ ЦЕЛЕЙ. Подробнее см. в Меньшей стандартной
//		общественной лицензии GNU.
//
//		Вы должны были получить копию Меньшей стандартной общественной лицензии GNU
//		вместе с этой программой. Если это не так, см.
//		<http://www.gnu.org/licenses/>.
#ifndef DEFINITIONS_GAME_H
#define DEFINITIONS_GAME_H

#define NOMINMAX
#define MY_FONT_COLOUR 0xff5b6b1b
#define MY_CODE_COLOUR 0xff4e677b
#define MY_TASK_COLOUR 0xff4b5b0b

#ifdef ISILME_DLL
#define ISILME_API __declspec(dllexport)
#else
#define ISILME_API __declspec(dllimport)
#endif

#include <map>
#include <set>
#include <list>
#include <vector>
#include <string>
#include <deque>
#include <limits>

#include <Box2D/Box2D.h>

#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/signals.hpp>
#include <boost/signals2.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/enable_shared_from_this.hpp>

#include <tinyxml.h>

#ifdef __cplusplus
extern "C"
{
#endif
#include <lualib.h>
#ifdef __cplusplus
}
#endif

#include <luabind/lua_include.hpp>
#include <luabind/luabind.hpp>

#include <GUIChan/gui.hpp>

#include <hge.h>
#include <hgeanim.h>

#include "Debug.h"

//class IAction;
class Action;
typedef boost::shared_ptr<Action> ActionPtr;
typedef boost::weak_ptr<Action> ActionWPtr;
typedef std::set<ActionPtr>	ActionSet;

class ActionManager;
typedef boost::shared_ptr<ActionManager> ActionManagerPtr;

class Behaviour;
typedef boost::shared_ptr<Behaviour> BehaviourPtr;
typedef boost::weak_ptr<Behaviour> BehaviourWPtr;

class Body;
typedef boost::shared_ptr<Body> BodyPtr;
typedef boost::weak_ptr<Body> BodyWPtr;

class Camera;
typedef boost::shared_ptr<Camera> CameraPtr;
typedef boost::weak_ptr<Camera> CameraWPtr;

class Entity;
typedef boost::shared_ptr<Entity> EntityPtr;
typedef boost::weak_ptr<Entity> EntityWPtr;

class Game;
class InputSystem;
class Joint;

class Layer;
typedef boost::shared_ptr<Layer> LayerPtr;
typedef boost::weak_ptr<Layer> LayerWPtr;

class Level;
typedef boost::shared_ptr<Level> LevelPtr;
typedef boost::weak_ptr<Level> LevelWPtr;

class Renderer;
class ResourceManager;
class SoundSystem;
class State;
typedef boost::shared_ptr<State> StatePtr;

class StateManager;
class Script;
typedef Script* ScriptPtr;

class Scheduler;
typedef boost::shared_ptr<Scheduler> SchedulerPtr;

class ScheduleManager;
typedef ScheduleManager* ScheduleManagerPtr;

class FactoryManager;
typedef boost::shared_ptr<FactoryManager> FactoryPtr;

typedef std::list<StatePtr>	StateList;

class Trigger;
typedef boost::shared_ptr<Trigger> TriggerPtr;

class BodyDef;
class ActionDefinition;

class BehaviourDefinition;
typedef boost::shared_ptr<BehaviourDefinition> BehaviourDefPtr;

class EntityDefinition;
typedef boost::shared_ptr<EntityDefinition> EntityDefPtr;

class GraphicsDefinition;
typedef boost::shared_ptr<GraphicsDefinition> GraphicsDefPtr;

class CameraDefinition;
typedef boost::shared_ptr<CameraDefinition> CameraDefPtr;

class Graphics;
typedef boost::shared_ptr<Graphics> GraphicsPtr;
typedef boost::weak_ptr<Graphics> GraphicsWPtr;

class Query;
typedef boost::shared_ptr<Query> QueryPtr;

class MasterFile;
typedef boost::shared_ptr<MasterFile> MasterFilePtr;

class Category;
typedef boost::shared_ptr<Category> CategoryPtr;

class Entry;
typedef boost::shared_ptr<Entry> EntryPtr;

class IBehaviourFactory;
typedef boost::shared_ptr<IBehaviourFactory> BehaviourFactoryPtr;

class IGraphicsFactory;
typedef boost::shared_ptr<IGraphicsFactory> GraphicsFactoryPtr;

/// @namespace graphics
/// Графические модели, используемые для визуализации сущностей
namespace graphics
{
	class Sprite;
	typedef boost::shared_ptr<Sprite> SpritePtr;

	class Animation;
	typedef boost::shared_ptr<Animation> AnimationPtr;

	class TriggerGraphics;
};

namespace inventory
{
	class IItemFactory;
	typedef boost::shared_ptr<IItemFactory> ItemFactoryPtr;
	typedef std::map<std::string, ItemFactoryPtr> ItemFactoryMap;

	class ItemDef;
	typedef boost::shared_ptr<ItemDef>	ItemDefPtr;

	class Item;
	typedef boost::shared_ptr<Item> ItemPtr;
	typedef boost::weak_ptr<Item> ItemWPtr;
	typedef std::vector<ItemPtr> ItemsList;

	class Inventory;
	typedef boost::shared_ptr<Inventory> InventoryPtr;
	typedef boost::weak_ptr<Inventory> InventoryWPtr;
};

namespace serialisation
{
	class DynamicLevelSerialiser;

	class SaveData;
	typedef boost::shared_ptr<SaveData> SaveDataPtr;
	
	class SaveManager;
	typedef boost::shared_ptr<SaveManager> SaveManagerPtr;
};

class EntityPalette;
typedef boost::shared_ptr<EntityPalette> EntityPalettePtr;

class AIPalette;
typedef boost::shared_ptr<AIPalette> AIPalettePtr;

class Fraction;
typedef boost::shared_ptr<Fraction> FractionPtr;
typedef boost::weak_ptr<Fraction> FractionWptr;

class Rank;
typedef boost::shared_ptr<Rank> RankPtr;
typedef boost::weak_ptr<Rank> RankWPtr;
class FractionManager;
class FractionInfo;
typedef boost::shared_ptr<FractionInfo> FractionInfoPtr;

typedef std::list<std::string>					StringList;
typedef std::map<std::string, std::string>		StringMap;
typedef std::map<std::string, float>			AttributeMap;
typedef std::set<EntityPtr>						EntitySet;
typedef std::map<std::string, EntityPtr>		EntityMap;
typedef std::list<EntityPtr>					EntityList;
typedef std::set<EntityPtr>						EntitySet;

/// Определения, относящиеся к Box2D
typedef b2Vec2									Vector2;
typedef b2Fixture								Fixture;
typedef std::list<b2FixtureDef*>				FixtureDefList;
typedef std::map<std::string, b2FixtureDef*>	FixtureDefMap;
typedef std::map<std::string, Fixture*>			FixtureMap;

/// Математические макросы
#define sqr(a) ((a)*(a))

#include "Core/Log.h"

#endif