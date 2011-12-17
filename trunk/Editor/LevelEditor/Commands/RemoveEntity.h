#pragma once
#include "../Stdafx.h"

using namespace LevelEditor::Proxy;

namespace LevelEditor
{
	namespace Commands
	{
		public ref class RemoveEntity : public Common::ICommand
		{
		public:
			RemoveEntity(LayerProxy^ level, EntityProxy^ entity);

			virtual void Execute();

			virtual void Unexecute();
		private:
			LayerProxy^ mLayer;
			EntityProxy^ mEntity;
		};
	}
}