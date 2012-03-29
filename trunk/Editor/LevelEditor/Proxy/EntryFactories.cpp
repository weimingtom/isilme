#include "Stdafx.h"
#include "ModuleProxy.h"
#include "EntryFactories.h"
#include "Engine\Core\MasterFile.h"
#include "ScriptFileProxy.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace LevelEditor
{
	namespace Proxy
	{

		EntryProxy^ LevelEntryFactory::CreateNewEntry()
		{
			LevelPtr level(new Level());
			LevelEntry* e = new LevelEntry("");
			e->data = level;

			EntryPtr entry(e);
			return gcnew EntryProxy(entry);
		}

		EntryProxy^ ScriptEntryFactory::CreateNewEntry()
		{
			EditableScriptEntry* e = new EditableScriptEntry("");
			e->Source = "";

			EntryPtr entry(e);
			return gcnew EntryProxy(entry);
		}

		EntryProxy^ ConversationEntryFactory::CreateNewEntry()
		{
			return nullptr;
		}

	}
}