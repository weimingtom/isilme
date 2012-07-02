#pragma once
#include "../Stdafx.h"
#include "../SharedCLIPtr.h"

using namespace Common;
using namespace LevelEditor::Proxy;

namespace LevelEditor
{
	namespace Commands
	{
		public ref class ScaleEntity : public Common::ICommand
		{
		public:
			virtual void Execute();
			virtual void Unexecute();

			ScaleEntity(EntityProxy^ entity, float scale);
		private:
			EntityProxy^ mEntity;
			float mOldScale;
			float mNewScale;

		};
	}
}