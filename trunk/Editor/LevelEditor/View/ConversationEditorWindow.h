#pragma once

#include "../Stdafx.h"

namespace LevelEditor
{
	namespace View
	{
		public ref class ConversationEditorWindow : public Common::Views::EditorWindow
		{
		public:
			ConversationEditorWindow();

			virtual void Load(Common::IEditableData^ data) override;
		private:
			/// Dialog tree
			System::Windows::Controls::TreeView^	mDialogTree;

			/// Conversation for editing
			Proxy::ConversationProxy^ mConversation;
		};
	}
}