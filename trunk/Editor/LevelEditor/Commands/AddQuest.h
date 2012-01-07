#pragma once
#include "../Stdafx.h"

using namespace System;
using namespace LevelEditor::Proxy;

namespace LevelEditor
{
	namespace Commands
	{
		public ref class AddQuest
		{
		public:
		private:
			StoryProxy^ mStory;
		};
	}
}