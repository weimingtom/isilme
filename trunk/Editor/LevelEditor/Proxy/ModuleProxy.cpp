#include "Stdafx.h"
#include "ModuleProxy.h"

namespace LevelEditor
{
	namespace Proxy
	{
		ObservableCollection<LevelProxy^>^ ModuleProxy::Levels::get()
		{
			return mLevels;
		}

		ObservableCollection<ConversationProxy^>^ ModuleProxy::Conversations::get()
		{
			return mConversations;
		}

		StoryProxy^ ModuleProxy::Story::get()
		{
			return mStory;
		}

		ModuleProxy::ModuleProxy()
		{

		}

		void ModuleProxy::AddLevel( LevelProxy^ level )
		{

		}

		void ModuleProxy::AddConversation( ConversationProxy^ conversation )
		{

		}

		void ModuleProxy::RemoveLevel( LevelProxy^ level )
		{

		}

		void ModuleProxy::RemoveConversation( ConversationProxy^ conversation )
		{

		}

	}
}