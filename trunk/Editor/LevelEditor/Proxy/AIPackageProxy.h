#pragma once

#include "../Stdafx.h"

namespace LevelEditor
{
	namespace Proxy
	{
		public ref class AIPackageProxy : public Common::ProxyObject
		{
		public:
			property System::String^ ID
			{
				System::String^ get();
				void set(System::String^ value);
			}
		};
	}
}