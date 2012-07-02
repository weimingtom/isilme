#pragma once
#include "../Stdafx.h"

using namespace System;
using namespace LevelEditor::Proxy;

namespace LevelEditor
{
	namespace Commands
	{
		public ref class AddPhrase : public Common::ICommand
		{
		public:
			AddPhrase(ConversationProxy^ conversation, PhraseProxy^ phrase);
			AddPhrase(PhraseProxy^ parent, PhraseProxy^ child);

			virtual void Execute();
			virtual void Unexecute();
		private:
			ConversationProxy^ mConversation;
			PhraseProxy^ mParentPhrase;
			PhraseProxy^ mPhrase;
		};
	}
}