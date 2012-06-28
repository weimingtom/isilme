#pragma once
#include "../Stdafx.h"

using namespace LevelEditor::Proxy;

namespace LevelEditor
{
	namespace Commands
	{
		public ref class MoveLayer : public Common::ICommand
		{
		public:
			MoveLayer(LayerProxy^ layer, int position);

			virtual void Execute();
			virtual void Unexecute();
		private:
			LayerProxy^ mLayer;
			LevelProxy^ mLevel;
			int mOldPosition;
			int mNewPosition;
		};
	}
}