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
		ref class PointTypeConvertor;

		[System::ComponentModel::TypeConverter(PointTypeConvertor::typeid)]
		public value class Point
		{
		public:
			[NotifyParentProperty(true)]
			property float X
			{
				float get () { return mX;}
				void set (float value) {mX = value;}
			}
			[NotifyParentProperty(true)]
			property float Y
			{
				float get () { return mY;}
				void set (float value) {mY = value;}
			}
		private:
			float mX, mY;
		};

		public ref class PointTypeConvertor : public ExpandableObjectConverter
		{
		public:
			virtual bool CanConvertTo(ITypeDescriptorContext^ context, System::Type^ destinationType) override
			{
				if (destinationType == Point::typeid) return true;
				else return ExpandableObjectConverter::CanConvertTo(context, destinationType);
			}

			virtual Object^ ConvertTo(ITypeDescriptorContext^ context, System::Globalization::CultureInfo^ culture, Object^ value, System::Type^ destinationType) override
			{
				if (destinationType == String::typeid && dynamic_cast<Point^>(value))
				{
					Point^ vec = (Point^)value;
					return String::Format("{0}, {1}", vec->X, vec->Y);
				}
				else return ExpandableObjectConverter::ConvertTo(context, culture, value, destinationType);
			}

			virtual bool CanConvertFrom(ITypeDescriptorContext^ context, System::Type^ sourceType) override
			{
				if (sourceType == String::typeid) 
					return true;
				else 
					return ExpandableObjectConverter::CanConvertFrom(context, sourceType);
			}

			virtual Object^ ConvertFrom(ITypeDescriptorContext^ context, System::Globalization::CultureInfo^ culture, Object^ value) override
			{
				if (dynamic_cast<String^>(value) != nullptr)
				{
						String^ strVal = dynamic_cast<String^>(value);
						array<String^>^ parts = strVal->Split(',');
						float x = float::Parse(parts[0]);
						float y = float::Parse(parts[1]);
						Point^ p = gcnew Point();
						p->X = x;
						p->Y = y;
						return p;
				}
				else return ExpandableObjectConverter::ConvertFrom(context, culture, value);
			}
		};

		[Serializable]
		public ref class EntityCopyData
		{
		public:
			String^ Type;
			float Angle;
			float Scale;
		};

		public ref class EntityProxy : public ProxyObject
		{
		public:
			EntityProxy(EntityPtr entity);
			virtual ~EntityProxy();

			[System::ComponentModel::Browsable(false)]
			property LayerProxy^ Layer
			{
				LayerProxy^ get();
				void set(LayerProxy^ value);
			}

			property System::String^ Name
			{
				System::String^ get();
			}

			property float Scale
			{
				float get();
				void set(float value);
			}

			property float Angle
			{
				float get();
				void set(float value);
			}

			[System::ComponentModel::TypeConverter(PointTypeConvertor::typeid)]
			[NotifyParentProperty(true)]
			property Proxy::Point Position
			{
				Proxy::Point get();
				void set(Proxy::Point value);
			}

			property String^ Type
			{
				String^ get();
			}

			EntityCopyData^ MakeCopy();
		internal:
			SharedCLIPtr<Entity>* mEntity;

			///< Прокси-слой, содержащий сущность
			LayerProxy^ mLayer;

			Point p;
			String^ mType;
		};
	}
}