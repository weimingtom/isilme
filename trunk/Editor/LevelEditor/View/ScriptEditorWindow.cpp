#include "Stdafx.h"
#include "ScriptEditorWindow.h"
#include "..\Proxy\ScriptProxy.h"

namespace LevelEditor
{
	namespace View
	{
		ScriptEditorWindow::ScriptEditorWindow()
		{
			System::Windows::Controls::Grid^ grid = gcnew System::Windows::Controls::Grid();
			mEditor = gcnew ICSharpCode::AvalonEdit::TextEditor();
			grid->Children->Add(mEditor);
			AddChild(grid);
		}

		void ScriptEditorWindow::Load( Common::IEditableData^ data )
		{

			mScript = dynamic_cast<Proxy::ScriptProxy^>(data->Data);
			if (mScript != nullptr)
			{
				mEditor->Text = mScript->Text;
				//mEditor->Language="lua";
				//mEditor->SetBinding(ICSharpCode::AvalonEdit::, gcnew System::Windows::Data::Binding("Name"));
			}
		}

		void ScriptEditorWindow::Load()
		{

		}

		void ScriptEditorWindow::Save()
		{
			mScript->Text = mEditor->Text;
		}

	}
}