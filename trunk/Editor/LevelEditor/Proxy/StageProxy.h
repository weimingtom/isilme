#pragma once
#include "../Stdafx.h"
#include "../SharedCLIPtr.h"

using namespace System;
using namespace System::Collections::ObjectModel;

namespace LevelEditor
{
	namespace Proxy
	{
		public ref class StageProxy : public Common::ProxyObject
		{
		public:
			StageProxy(story::StagePtr stage);
			virtual ~StageProxy();

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
		private:
		internal:
			String^ mOnStart;
			String^ mOnUpdate;
			SharedCLIPtr<story::Stage>* mStage;
		};
	}
}