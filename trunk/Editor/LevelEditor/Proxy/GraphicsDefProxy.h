#pragma once
#include "../Stdafx.h"

namespace LevelEditor
{
	namespace Proxy
	{
		public ref class GraphicsDefProxy : public Common::ProxyObject
		{
		public:
			property String^ ID
			{
				String^ get();
				void set();
			}
		};
	}
}