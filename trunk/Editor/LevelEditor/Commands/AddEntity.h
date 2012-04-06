#pragma once
#include "../Stdafx.h"
#include "../SharedCLIPtr.h"

using namespace Common;
using namespace LevelEditor::Proxy;

namespace LevelEditor
{
	namespace Commands
	{
		public ref class AddEntity : public Common::ICommand
		{
		public:
			virtual void Execute();
			virtual void Unexecute();

			AddEntity(LayerProxy^ layer, EntityProxy^ entity);
			virtual ~AddEntity();
		private:
			EntityProxy^ mEntity;
			LayerProxy^ mLayer;

		};
	}
}