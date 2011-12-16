#pragma once
#include "../Stdafx.h"
#include "../SharedCLIPtr.h"
#include "Engine/Editor/AddEntityCommand.h"

using namespace Common;

namespace LevelEditor
{
	namespace Commands
	{
		public ref class AddEntity : public Common::ICommand
		{
		public:
			virtual void Execute();
			virtual void Unexecute();

			AddEntity(LayerPtr layer, EntityPtr entity);
			virtual ~AddEntity();
		private:
			SharedCLIPtr<Entity>* mEntity;
			SharedCLIPtr<Layer>* mLayer;

		};
	}
}