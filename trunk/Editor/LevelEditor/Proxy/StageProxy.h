﻿#pragma once
#include "../Stdafx.h"
#include "../SharedCLIPtr.h"

using namespace System;
using namespace System::Collections::ObjectModel;

namespace LevelEditor
{
	namespace Proxy
	{
		[Serializable]
		public ref class StageCopyData
		{
		public:
			int ID;
			String^ Text;
		};

		public ref class StageProxy : public Common::ProxyObject
		{
		public:
			StageProxy();
			StageProxy(story::StagePtr stage);
			StageProxy(StageCopyData^ date);

			virtual ~StageProxy();

			StageCopyData^	MakeCopy();

			property String^ Text
			{
				String^ get();
				void set(String^ value);
			}

			property String^ OnStart
			{
				String^ get();
				void set(String^ value);
			}

			property String^ OnUpdate
			{
				String^ get();
				void set(String^ value);
			}

			property int ID
			{
				int get();
				void set(int value);
			}

			property QuestProxy^ Quest
			{
				QuestProxy^ get();
			}
		private:
		internal:
			String^ mOnStart;
			String^ mOnUpdate;
			QuestProxy^ mQuest;
			SharedCLIPtr<story::Stage>* mStage;
		};
	}
}