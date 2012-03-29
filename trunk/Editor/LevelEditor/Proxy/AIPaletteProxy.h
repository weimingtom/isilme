#pragma once
#include "../Stdafx.h"

namespace LevelEditor
{
	namespace Proxy
	{
		public ref class AIPaletteProxy : public Coomon::ProxyObject
		{
		public:
			AIPaletteProxy();

			static property AIPaletteProxy^	Instance
			{
				AIPaletteProxy^ get();
			}

		internal:
			SharedCLIPtr<AIPalette>* mPalette;
		private:
			static AIPaletteProxy^ mInstance = nullptr;
		};
	}
}