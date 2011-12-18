#pragma once
using namespace Common;

#include "../Stdafx.h"
#include "../SharedCLIPtr.h"

using namespace System;
using namespace System::ComponentModel::Design;
using namespace System::ComponentModel;

namespace LevelEditor
{
	namespace Proxy
	{
		public ref class MyExpandableObjectConverter : ExpandableObjectConverter
		{
		public:
			virtual bool CanConvertFrom(ITypeDescriptorContext^ context, Type^ sourceType) override
			{
				if (sourceType == String::typeid) 
					return true;
				else 
					return ExpandableObjectConverter::CanConvertFrom(context, sourceType);
			}
		};

		public value class Point
		{
		public:
			property float X
			{
				float get () { return mX;}
				void set (float value) {mX = value;}
			}
			property float Y
			{
				float get () { return mY;}
				void set (float value) {mY = value;}
			}
		private:
			float mX, mY;
		};

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

			property float Angle
			{
				float get();
				void set(float value);
			}

			[System::ComponentModel::TypeConverter(MyExpandableObjectConverter::typeid)]
			property Point^ Position
			{
				Point^ get();
				void set(Point^ value);
			}
		internal:
			SharedCLIPtr<Entity>* mEntity;

			///< Прокси-слой, содержащий сущность
			LayerProxy^ mLayer;
		};
	}
}