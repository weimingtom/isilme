#pragma once

#include "../Stdafx.h"
#include "../Proxy/ScriptFileProxy.h"

namespace LevelEditor
{
	namespace View
	{
		public ref class ScriptEditorWindow : public Common::Views::EditorWindow
		{
		public:
			static System::Windows::Input::RoutedCommand^ Comment = gcnew System::Windows::Input::RoutedCommand();
			static System::Windows::Input::RoutedCommand^ Check = gcnew System::Windows::Input::RoutedCommand();
			static System::Windows::Input::RoutedCommand^ Uncomment = gcnew System::Windows::Input::RoutedCommand();
			static System::Windows::Input::RoutedCommand^ Compile = gcnew System::Windows::Input::RoutedCommand();

			ScriptEditorWindow();

			virtual void Load(Common::IEditableData^ data) override;

			virtual void Load() override;

			virtual void Save() override;

			virtual property bool IsModified
			{
				bool get() override;
			}
		protected:
			//virtual void CanExecuteSave(System::Object^ sender, System::Windows::Input::CanExecuteRoutedEventArgs^ e) override;
		private:
			ICSharpCode::AvalonEdit::TextEditor^ mEditor;
			Proxy::ScriptFileProxy^ mScript;
		};

		public ref class ScriptToolBar : public System::Windows::Controls::ToolBar
		{
		public:
			ScriptToolBar();

			static property ScriptToolBar^ Instance
			{
				ScriptToolBar^ get();
			}
		private:
			static ScriptToolBar^ mInstance = nullptr;
		};
	}
}