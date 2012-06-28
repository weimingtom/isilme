#include "Stdafx.h"
#include "LayerProxy.h"
#include "EntityProxy.h"

using namespace System::Runtime::InteropServices;

namespace LevelEditor
{
	namespace Proxy
	{
		LayerProxy::LayerProxy( LayerPtr layer )
		{
			mLayer = new SharedCLIPtr<Layer>(layer);
			mEntities = gcnew ObservableCollection<EntityProxy^>();
			mGrid = gcnew GridProxy();

			for (int i = 0; i < layer->Size(); ++i)
			{
				EntityProxy^ entity = gcnew EntityProxy(layer->GetEntity(i));
				mEntities->Add(entity);
				entity->Layer = this;
			}
		}

		void LayerProxy::AddEntity( EntityProxy^ entity )
		{
			// Добавляем сущность на сцену
			LayerPtr nativeLayer = mLayer->Value;
			EntityPtr nativeEntity = entity->mEntity->Value;
			nativeLayer->Add(nativeEntity);

			// Запоминаем отношения между прокси-объектами
			entity->mLayer = this;

			// Добавляем прокси-объект в коллекцию
			mEntities->Add(entity);
		}

		void LayerProxy::RemoveEntity( EntityProxy^ entity )
		{
			LayerPtr nativeLayer = mLayer->Value;
			EntityPtr nativeEntity = entity->mEntity->Value;
			nativeLayer->Remove(nativeEntity);

			entity->mLayer = nullptr;

			mEntities->Remove(entity);
		}

		ObservableCollection<EntityProxy^>^ LayerProxy::Entities::get()
		{
			return mEntities;
		}

		String^ LayerProxy::Name::get()
		{
			return gcnew String(mLayer->Value->GetName().c_str());
		}

		LevelProxy^ LayerProxy::Level::get()
		{
			return mLevel;
		}

		GridProxy^ LayerProxy::Grid::get()
		{
			return mGrid;
		}

		void LayerProxy::Grid::set(GridProxy^ value)
		{
			mGrid = value;
		}

		void LayerProxy::Name::set(String^ value)
		{
			mLayer->Value->SetName((char*)(Marshal::StringToHGlobalAnsi(value).ToPointer()));
			RaisePropertyChanged(this, "Name");
		}

		bool LayerProxy::Visible::get()
		{
			return mLayer->Value->IsVisible();
		}

		void LayerProxy::Visible::set(bool value)
		{
			mLayer->Value->SetVisible(value);
			RaisePropertyChanged(this, "Visible");
		}
	}
}