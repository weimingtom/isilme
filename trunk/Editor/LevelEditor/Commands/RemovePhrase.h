#pragma once
#include "../Stdafx.h"

using namespace System;
using namespace LevelEditor::Proxy;

namespace LevelEditor
{
	namespace Commands
	{
		public ref class RemovePhrase : public Common::ICommand
		{
		public:
			RemovePhrase(PhraseProxy^ phrase);

			virtual void Execute();
			virtual void Unexecute();
		private:
			ConversationProxy^ mConversation;
			PhraseProxy^ mParentPhrase;
			PhraseProxy^ mPhrase;
		};
	}
}