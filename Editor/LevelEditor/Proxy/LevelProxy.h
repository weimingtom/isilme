#pragma once
#include "../Stdafx.h"
#include "../SharedCLIPtr.h"

using namespace System;
using namespace System::Collections::ObjectModel;

namespace LevelEditor
{
	namespace Proxy
	{
		public ref class LevelProxy : public Common::ProxyObject
		{
		public:
			LevelProxy(LevelPtr level);
			virtual ~LevelProxy();

			property ObservableCollection<LayerProxy^>^ Layers
			{
				ObservableCollection<LayerProxy^>^ get();
			}

			void AddLayer(LayerProxy^ layer);

			void RemoveLayer(LayerProxy^ layer);

			property String^ ID
			{
				String^ get();
			}
		private:
			ObservableCollection<LayerProxy^>^ mLayers;

			String^ mID;
		internal:
			SharedCLIPtr<Level>* mLevel;
		};
	}
}