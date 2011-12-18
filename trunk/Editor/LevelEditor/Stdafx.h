// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#include <Isilme.h>

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