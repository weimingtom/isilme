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

		public ref class LayerProxy : ProxyObject
		{
		public:
			LayerProxy(LayerPtr layer);


			/// �������� �������� �� ����
			///
			/// @param entity	����������� ������
			void AddEntity(EntityProxy^ entity);


			/// ������� ������ �� ����
			///
			/// @param [in,out]	entity	If non-null, the entity.
			void RemoveEntity(EntityProxy^ entity);

			/// ���������� ��������� �������� ����
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

		internal:
			LevelProxy^ mLevel;
		
			SharedCLIPtr<Layer>* mLayer;
		private:
			ObservableCollection<EntityProxy^>^ mEntities;
		};
	}
}