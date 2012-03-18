#pragma once

#include "../Stdafx.h"
#include "IEntryFactory.h"

using namespace System;

namespace LevelEditor
{
	namespace Proxy
	{
		public ref class LevelEntryFactory : public IEntryFactory
		{
		public:
			virtual EntryProxy^ CreateNewEntry();
		};

		public ref class ScriptEntryFactory : public IEntryFactory
		{
		public:
			virtual EntryProxy^ CreateNewEntry();
		};

		public ref class ConversationEntryFactory : public IEntryFactory
		{
		public:
			virtual EntryProxy^ CreateNewEntry();
		};
	}
}