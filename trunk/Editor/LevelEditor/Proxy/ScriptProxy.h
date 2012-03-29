#pragma once

#include "../Stdafx.h"
#include "IDataToProxyConverter.h"

using namespace System;

namespace LevelEditor
{
	namespace Proxy
	{
		public ref class ScriptProxy : public Common::ProxyObject
		{
		public:
			
		private:
			ScriptPtr mScript;
		};

	}
}