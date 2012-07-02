#include "Stdafx.h"
#include "LevelProxy.h"
#include "LayerProxy.h"

namespace LevelEditor
{
	namespace Proxy
	{
		ObservableCollection<LayerProxy^>^ LevelProxy::Layers::get()
		{
			return mLayers;
		}

		LevelProxy::LevelProxy( LevelPtr level )
		{
			mLayers = gcnew ObservableCollection<LayerProxy^>();

			mLevel = new SharedCLIPtr<Level>(level);

			// Добавляем дочерние слои, которые уже существовали на уровне
			for (int i = 0; i < level->GetLayersCount(); ++i)
			{
				LayerProxy^ layer = gcnew LayerProxy(level->GetLayer(i));
				mLayers->Add(layer);
				layer->mLevel = this;
			}

			mID = gcnew String(level->GetID().c_str());
		}

		LevelProxy::~LevelProxy()
		{
			delete mLevel;
		}

		void LevelProxy::AddLayer( LayerProxy^ layer )
		{
			mLevel->Value->AddLayer(layer->mLayer->Value);
			mLayers->Add(layer);
			layer->mLevel = this;
		}

		void LevelProxy::RemoveLayer( LayerProxy^ layer )
		{
			mLevel->Value->RemoveLayer(layer->mLayer->Value);
			mLayers->Remove(layer);
			layer->mLevel = nullptr;
		}

		String^ LevelProxy::ID::get()
		{
			return mID;
		}
	}
}