#include "Stdafx.h"

using namespace Common;
using namespace System::Windows::Input;

namespace LevelEditor
{
	public ref class LevelEditorCommands
	{
	public:
		static DelegateCommand^ SelectObjectsSelector = gcnew DelegateCommand();
		static DelegateCommand^ SelectEntityBrush = gcnew DelegateCommand();
		static DelegateCommand^ ActivateGrid = gcnew DelegateCommand();
		static DelegateCommand^ ActivatePhisics = gcnew DelegateCommand();
		static DelegateCommand^ DrawPhisics = gcnew DelegateCommand();
	};

	public ref class ConversationEditorCommands
	{
	public:
		static DelegateCommand^ AddPhrase = gcnew DelegateCommand();
		static RoutedUICommand^ AddRefPhrase = gcnew RoutedUICommand();
	};

	public ref class QuestEditorCommands
	{
		static DelegateCommand^ AddQuest = gcnew DelegateCommand();
		static DelegateCommand^ AddStage = gcnew DelegateCommand();
	};
}