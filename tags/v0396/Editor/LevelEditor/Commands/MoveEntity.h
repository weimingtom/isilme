#pragma once
#include "../Stdafx.h"

using namespace LevelEditor::Proxy;

namespace LevelEditor
{
	namespace Commands
	{
		public ref class MoveEntity : public Common::ICommand
		{
		public:
			MoveEntity(EntityProxy^ entity, Proxy::Point^ position);

			virtual void Execute();
			virtual void Unexecute();
		private:
			EntityProxy^ mEntity;
			Proxy::Point^ mOldPosition;
			Proxy::Point^ mNewPosition;
		};
	}
}