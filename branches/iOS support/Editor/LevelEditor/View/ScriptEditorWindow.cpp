#include "Stdafx.h"
#include "ScriptEditorWindow.h"
#include "../Proxy/ScriptFileProxy.h"
#include <iostream>
#include <fstream>
#include "..\ResourceHelper.h"

using namespace System::Windows::Controls;
using namespace System::Windows::Media;
using namespace System;

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

			mScript = dynamic_cast<Proxy::ScriptFileProxy^>(data->Data);
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

		ScriptToolBar::ScriptToolBar()
		{
			// Comment button
			Button^ mComment = gcnew Button();
			mComment->Command = ScriptEditorWindow::Comment;
			Image^ image = gcnew System::Windows::Controls::Image();
			image->Source = ResourceHelper::GetPngSource("Comment.png");
			mComment->Content = image;
			mComment->ToolTip = "Comment script code";

			// Uncomment button
			Button^ mUncomment = gcnew Button();
			mUncomment->Command = ScriptEditorWindow::Uncomment;
			image = gcnew System::Windows::Controls::Image();
			image->Source = ResourceHelper::GetPngSource("Uncomment.png");
			mUncomment->Content = image;
			mUncomment->ToolTip = "Uncomment script code";

			// Compile
			Button^ mCompile = gcnew Button();
			mCompile->Command = ScriptEditorWindow::Compile;
			image = gcnew System::Windows::Controls::Image();
			image->Source = ResourceHelper::GetPngSource("Compile.png");
			mCompile->Content = image;
			mCompile->ToolTip = "Uncomment script code";

			// Check
			Button^ mCheck = gcnew Button();
			mCheck->Command = ScriptEditorWindow::Check;
			image = gcnew System::Windows::Controls::Image();
			image->Source = ResourceHelper::GetPngSource("Check.png");
			mCheck->Content = image;
			mCheck->ToolTip = "Check valid";

			AddChild(mComment);
			AddChild(mUncomment);
			AddChild(mCheck);
			AddChild(mCompile);
		}

		ScriptToolBar^ ScriptToolBar::Instance::get()
		{
			if (mInstance == nullptr)
			{
				mInstance = gcnew ScriptToolBar();
			}

			return mInstance;
		}

	}
}