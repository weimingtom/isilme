#ifndef DEFINITIONS_GAME_H
#define DEFINITIONS_GAME_H

#define MY_FONT_COLOUR 0xff5b6b1b
#define MY_CODE_COLOUR 0xff4e677b
#define MY_TASK_COLOUR 0xff4b5b0b

#ifdef ISILME_DLL
#define IsilmeExport __declspec(dllexport)
#else
#define IsilmeExport __declspec(dllimport)
#endif

#include <map>
#include <set>
#include <list>
#include <vector>
#include <string>
#include <deque>
#include <Box2D/Box2D.h>

#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/signals.hpp>
#include <boost/signals2.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/enable_shared_from_this.hpp>

#include <tinyxml.h>

#include <luabind/lua_include.hpp>
#include <luabind/luabind.hpp>

class ISensor;

template <class T> class Sensor;
typedef boost::shared_ptr<ISensor> SensorPtr;

class IStrategy;
typedef boost::shared_ptr<IStrategy> StrategyPtr;
typedef boost::weak_ptr<IStrategy> StrategyWPtr;

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
typedef std::map<std::string, GraphicsDefPtr> GraphicsPalette;

class CameraDefinition;
typedef boost::shared_ptr<CameraDefinition> CameraDefPtr;

class Graphics;
typedef boost::shared_ptr<Graphics> GraphicsPtr;
typedef boost::weak_ptr<Graphics> GraphicsWPtr;
typedef std::map<std::string, GraphicsPtr> GraphicsMap;

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
	typedef std::map<std::string, ItemDefPtr> ItemsPalette;

	class Item;
	typedef boost::shared_ptr<Item> ItemPtr;
	typedef boost::weak_ptr<Item> ItemWPtr;
	typedef std::vector<ItemPtr> ItemsList;

	class Inventory;
	typedef boost::shared_ptr<Inventory> InventoryPtr;
	typedef boost::weak_ptr<Inventory> InventoryWPtr;
};

typedef std::list<SensorPtr> SensorList;

typedef std::list<std::string>					StringList;
typedef std::map<std::string, std::string>		StringMap;
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

#endif