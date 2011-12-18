#pragma once

#include "../Stdafx.h"
#include "../SharedCLIPtr.h"

using namespace Common;
using namespace System;
using namespace System::Collections::ObjectModel;

namespace LevelEditor
{
	namespace Proxy
	{

		ref class EntityProxy;

		public ref class GridProxy
		{
		public:
			GridProxy()
			{
				Step = 1.0f;
			}
			GridProxy(float step)
			{
				Step = step;
			}

			property float Step
			{
				float get()
				{
					return mStep;
				}
				void set(float value)
				{
					mStep = value;
				}
			}
		private:
			float mStep;
		};

		public ref class LayerProxy : ProxyObject
		{
		public:
			LayerProxy(LayerPtr layer);


			/// Добавить сущность на слой
			///
			/// @param entity	Добавляемый объект
			void AddEntity(EntityProxy^ entity);


			/// Удаляет объект из слоя
			///
			/// @param [in,out]	entity	If non-null, the entity.
			void RemoveEntity(EntityProxy^ entity);

			/// Возвращает коллекцию объектов слоя
			///
			/// @return	The entities.
			property ObservableCollection<EntityProxy^>^ Entities
			{
				ObservableCollection<EntityProxy^>^ get();
			}

			property String^ Name
			{
				String^ get();
			}

			property LevelProxy^ Level
			{
				LevelProxy^ get();
			}

			property GridProxy^ Grid
			{
				GridProxy^ get();
				void set(GridProxy^ value);
			}
		internal:
			LevelProxy^ mLevel;

			GridProxy^ mGrid;
		
			SharedCLIPtr<Layer>* mLayer;
		private:
			ObservableCollection<EntityProxy^>^ mEntities;
		};
	}
}