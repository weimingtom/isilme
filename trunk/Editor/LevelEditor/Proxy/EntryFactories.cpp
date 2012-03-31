#include "Stdafx.h"
#include "ModuleProxy.h"
#include "EntryFactories.h"
#include "Engine\Core\MasterFile.h"
#include "ScriptFileProxy.h"
#include "..\ResourceHelper.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace LevelEditor
{
	namespace Proxy
	{

		EntryProxy^ LevelEntryFactory::CreateNewEntry(String^ fileName, String^ id)
		{
			LevelPtr level(new Level());
			LevelEntry* e = new LevelEntry(ResourceHelper::StringToChar(fileName));
			e->data = level;

			EntryPtr entry(e);
			return gcnew EntryProxy(entry);
		}

		EntryProxy^ ScriptEntryFactory::CreateNewEntry(String^ fileName, String^ id)
		{
			EditableScriptEntry* e = new EditableScriptEntry(ResourceHelper::StringToChar(fileName));
			e->Source = "";

			EntryPtr entry(e);
			return gcnew EntryProxy(entry);
		}

		EntryProxy^ ConversationEntryFactory::CreateNewEntry(String^ fileName, String^ id)
		{
			story::ConversationPtr conv(new story::Conversation(ResourceHelper::StringToChar(id)));
			ConversationEntry* e = new ConversationEntry(ResourceHelper::StringToChar(fileName));
			e->data = conv;

			EntryPtr entry(e);

			return gcnew EntryProxy(entry);
		}

	}
}