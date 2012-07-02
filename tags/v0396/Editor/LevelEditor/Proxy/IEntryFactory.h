#pragma once

#include "../Stdafx.h"

namespace LevelEditor
{
	namespace Proxy
	{
		public interface class IEntryFactory
		{
			EntryProxy^ CreateNewEntry(String^ fileName, String^ id);
		};
	}
}