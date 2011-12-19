#include "Stdafx.h"

using namespace Common;

namespace LevelEditor
{
	public ref class LevelEditorCommands
	{
	public:
		static DelegateCommand^ SelectObjectsSelector = gcnew DelegateCommand();
		static DelegateCommand^ SelectEntityBrush = gcnew DelegateCommand();
		static DelegateCommand^ ActivateGrid = gcnew DelegateCommand();
	};
}