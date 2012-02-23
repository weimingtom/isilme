#pragma once

#include "../Stdafx.h"
#include "../Proxy/ScriptProxy.h"

namespace LevelEditor
{
	namespace View
	{
		public ref class ScriptEditorWindow : public Common::Views::EditorWindow
		{
		public:
			ScriptEditorWindow();

			virtual void Load(Common::IEditableData^ data) override;

			virtual void Load() override;

			virtual void Save() override;
		private:
			ICSharpCode::AvalonEdit::TextEditor^ mEditor;
			Proxy::ScriptProxy^ mScript;
		};
	}
}