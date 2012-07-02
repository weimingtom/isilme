#pragma once
#include "../Stdafx.h"
#include "../SharedCLIPtr.h"
#include "Engine/Core/MasterFile.h"

namespace LevelEditor
{
	namespace Proxy
	{
		public interface class IDataToProxyConverter
		{
			Common::IProxyObject^ Convert(SharedCLIPtr<Entry>* entry);
		};
	}
}