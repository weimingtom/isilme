#include "IsilmePCH.h"
#include "Speaker.h"
#include "Conversation.h"

namespace story
{


	Speaker::Speaker()
	{

	}

	Speaker::~Speaker()
	{

	}

	void Speaker::SetConversation( ConversationPtr conversation )
	{
		mConversation = conversation;
	}

	story::ConversationPtr Speaker::GetConversation() const
	{
		return mConversation;
	}

}