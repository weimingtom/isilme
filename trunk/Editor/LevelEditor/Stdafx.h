// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#include <Engine/Isilme.h>
#include <Engine/Story/Story.h>
#include <Engine/Story/Quest.h>
#include <Engine/Story/Stage.h>
#include <Engine/Story/Conversation.h>
#include <Engine/Story/Phrase.h>
#include <Engine/Serialisation/MasterLoader.h>
#include <Engine/Serialisation/EntryLoader.h>

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
		interface class IDataToProxyConverter;
		interface class IEntryFactory;

		ref class FolderProxy;
		ref class PaletteItemProxy;
		ref class EntityPaletteProxy;
		ref class LayerProxy;
		ref class EntityProxy;
		ref class LevelProxy;
		ref class ConversationProxy;
		ref class PhraseProxy;
		ref class ScriptProxy;
		ref class StoryProxy;
		ref class QuestProxy;
		ref class StageProxy;

		ref class EntryProxy;
		ref class CategoryProxy;
		ref class ModuleProxy;

		ref class AIPaletteProxy;
		ref class AIPackageProxy;
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