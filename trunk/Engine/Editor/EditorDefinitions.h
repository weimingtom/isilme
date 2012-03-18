#ifndef EDITOR_DEFINITIONS_H
#define EDITOR_DEFINITIONS_H

#include <map>
#include <set>
#include <vector>
#include <stack>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include "../Definitions.h"

namespace editor
{

class Command;
typedef boost::shared_ptr<Command> CommandPtr;
typedef boost::weak_ptr<Command> CommandWPtr;
typedef std::stack<CommandPtr> CommandStack;

class CommandManager;
typedef boost::shared_ptr<CommandManager> CommandManagerPtr;

class AddEntityCommand;
class DelEntityCommand;
class MoveEntityCommand;
class AddLayerCommand;
class DelLayerCommand;

class Tool;
typedef boost::shared_ptr<Tool> ToolPtr;
typedef boost::weak_ptr<Tool> ToolWPtr;

class EntityBrushTool;
typedef boost::shared_ptr<EntityBrushTool> EntityBrushToolPtr;
typedef boost::weak_ptr<EntityBrushTool> EntityBrushToolWPtr;

class SelectorTool;
typedef boost::shared_ptr<SelectorTool> SelectorToolPtr;
typedef boost::weak_ptr<SelectorTool> SelectorToolWPtr;

};
#endif