﻿#include "Stdafx.h"
#include "StageProxy.h"
#include "QuestProxy.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace LevelEditor
{
	namespace Proxy
	{
		StageProxy::StageProxy( story::StagePtr stage )
		{
			mStage = new SharedCLIPtr<story::Stage>(stage);
		}

		StageProxy::StageProxy()
		{
			mStage = new SharedCLIPtr<story::Stage>(story::StagePtr(new story::Stage()));
		}

		StageProxy::StageProxy(StageCopyData^ data)
		{
			mStage = new SharedCLIPtr<story::Stage>(story::StagePtr(new story::Stage()));
			ID = data->ID;
			Text = data->Text;
		}

		StageProxy::~StageProxy()
		{
			delete mStage;
		}

		StageCopyData^ StageProxy::MakeCopy()
		{
			StageCopyData^ copy = gcnew StageCopyData();
			copy->ID = ID;
			copy->Text = Text;
			return copy;
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

		QuestProxy^ StageProxy::Quest::get()
		{
			return mQuest;
		}

		void StageProxy::OnStart::set(String^ value)
		{
		
		}

		void StageProxy::OnUpdate::set(String^ value)
		{
		
		}

		void StageProxy::ID::set(int value)
		{
			if (mQuest != nullptr)
				mQuest->mQuest->Value->RemoveStage(mStage->Value);
			mStage->Value->SetID(value);
			if (mQuest != nullptr)
				mQuest->mQuest->Value->AddStage(mStage->Value);
		}

		void StageProxy::Text::set(String^ value)
		{
			mStage->Value->SetText((char*)Marshal::StringToHGlobalAnsi(value).ToPointer());
		}
	}
}