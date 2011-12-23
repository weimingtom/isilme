#include "Stdafx.h"
#include "StageProxy.h"
#include "QuestProxy.h"

namespace LevelEditor
{
	namespace Proxy
	{
		StageProxy::StageProxy( story::StagePtr stage )
		{
			mStage = new SharedCLIPtr<story::Stage>(stage);
		}

		StageProxy::~StageProxy()
		{
			delete mStage;
		}

		String^ StageProxy::Text::get()
		{
			return gcnew String(mStage->Value->GetText().c_str());
		}

		int StageProxy::ID::get()
		{
			return mStage->Value->GetID();
		}

		String^ StageProxy::OnStart::get()
		{
			return "";
		}

		String^ StageProxy::OnUpdate::get()
		{
			return "";
		}

		void StageProxy::OnStart::set(String^ value)
		{
		
		}

		void StageProxy::OnUpdate::set(String^ value)
		{
		
		}

		void StageProxy::ID::set(int value)
		{
		
		}

		void StageProxy::Text::set(String^ value)
		{
		
		}
	}
}