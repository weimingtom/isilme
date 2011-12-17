#pragma once 
#include "../Stdafx.h"

using namespace LevelEditor::Proxy;

namespace LevelEditor
{
	namespace Commands
	{
		public ref class AddLayer : public Common::ICommand
		{
		public:
			AddLayer(LevelProxy^ level, LayerProxy^ layer);

			virtual void Execute();

			virtual void Unexecute();
		private:
			LevelProxy^ mLevel;
			LayerProxy^ mLayer;
		};
	}
}