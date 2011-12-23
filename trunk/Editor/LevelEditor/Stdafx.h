// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#include <Isilme.h>
#include "Engine/Quest/Story.h"
#include "Engine/Quest/Quest.h"
#include "Engine/Quest/Stage.h"
#include "Engine/Quest/Conversation.h"
#include "Engine/Quest/Phrase.h"

namespace LevelEditor
{
	namespace Tool
	{
		ref class ScrollerTool;
		ref class SelectorTool;
		ref class EntityBrush;
	}

	namespace Proxy
	{
		value class Point;
		interface class IHierarchicalProxy;
		ref class FolderProxy;
		ref class PaletteItemProxy;
		ref class EntityPaletteProxy;
		ref class LayerProxy;
		ref class EntityProxy;
		ref class LevelProxy;
		ref class ConversationProxy;
		ref class PhraseProxy;
		ref class StoryProxy;
		ref class QuestProxy;
		ref class StageProxy;
	}

	namespace Commands
	{
	
	}

	namespace View
	{
		ref class LevelEditorWindow;
		ref class LevelEditorToolBar;
		ref class ObjectManager;
	}
}