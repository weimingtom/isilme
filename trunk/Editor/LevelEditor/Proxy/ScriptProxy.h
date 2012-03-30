#pragma once

#include "../Stdafx.h"
#include "IDataToProxyConverter.h"

namespace LevelEditor
{
	namespace Proxy
	{
		public ref class ScriptProxy : public Common::ProxyObject
		{
		public:
			ScriptProxy(ScriptPtr script);
			virtual ~ScriptProxy();

			property System::String^  Source
			{
				System::String^ get();
				void set(System::String^ value);
			}
		private:
			System::String^ mSource;
			ScriptPtr mScript;
		};

	}
}