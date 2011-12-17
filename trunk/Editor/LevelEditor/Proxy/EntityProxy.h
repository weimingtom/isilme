#pragma once
using namespace Common;

#include "../Stdafx.h"
#include "../SharedCLIPtr.h"

using namespace System;

namespace LevelEditor
{
	namespace Proxy
	{
		public ref class EntityProxy : public ProxyObject
		{
		public:
			EntityProxy(EntityPtr entity);
			virtual ~EntityProxy();

			property LayerProxy^ Layer
			{
				LayerProxy^ get();
				void set(LayerProxy^ value);
			}

			property System::String^ Name
			{
				System::String^ get();
			}

			property float PositionX
			{
				float get()
				{
					return mEntity->Value->GetPosition().x;
				}
				void set(float value)
				{
					float y = mEntity->Value->GetPosition().y;
					mEntity->Value->SetPosition(value, y);
				}
			}
		internal:
			SharedCLIPtr<Entity>* mEntity;

			///< Прокси-слой, содержащий сущность
			LayerProxy^ mLayer;
		};
	}
}