#include "Stdafx.h"
#include "ScriptEditorWindow.h"
#include "..\Proxy\ScriptProxy.h"
#include <iostream>
#include <fstream>

namespace LevelEditor
{
	namespace View
	{
		ScriptEditorWindow::ScriptEditorWindow()
		{
			System::Windows::Controls::Grid^ grid = gcnew System::Windows::Controls::Grid();
			mEditor = gcnew ICSharpCode::AvalonEdit::TextEditor();
			mEditor->ShowLineNumbers = true;
			mEditor->SyntaxHighlighting = ICSharpCode::AvalonEdit::Highlighting::HighlightingManager::Instance->GetDefinition("Lua");
			grid->Children->Add(mEditor);
			AddChild(grid);
			IsCloseable = true;
			HideOnClose = false;
		}

		void ScriptEditorWindow::Load( Common::IEditableData^ data )
		{

			mScript = dynamic_cast<Proxy::ScriptProxy^>(data->Data);
			if (mScript != nullptr)
			{
				mEditor->Text = mScript->Text;
				mEditor->IsModified = false;
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
			std::string fname = (char*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(FileName).ToPointer();
			std::string text = (char*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(mEditor->Text).ToPointer();
			std::ofstream file;
			file.open(fname);
			file << text;
			file.close();
			mEditor->IsModified = false;

		}

		//void ScriptEditorWindow::CanExecuteSave( System::Object^ sender, System::Windows::Input::CanExecuteRoutedEventArgs^ e )
		//{
		//	e->CanExecute = mEditor->IsModified;
		//}

		bool ScriptEditorWindow::IsModified::get()
		{
			return mEditor->IsModified;
		}
	}
}