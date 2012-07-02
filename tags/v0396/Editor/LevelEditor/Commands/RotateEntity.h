#pragma  once
#include "../Stdafx.h"

using namespace LevelEditor::Proxy;

namespace LevelEditor
{
	namespace Commands
	{
		public ref class RotateEntity : public Common::ICommand
		{
		public:
			RotateEntity(EntityProxy^ entity, float angle);
			virtual void Execute();
			virtual void Unexecute();
		private:
			float mOldAnge;
			float mNewAngle;
			EntityProxy^ mEntity;
		};
	}
}