#include "Stdafx.h"
#include "EntityProxy.h"
#include "LayerProxy.h"
#include "../Commands/MoveEntity.h"
#include "../Commands/RotateEntity.h"
#include "../Commands/ScaleEntity.h"
namespace LevelEditor
{
	namespace Proxy
	{
		EntityProxy::EntityProxy( EntityPtr entity )
		{
			mType = gcnew String(entity->GetType().c_str());
			p = Point();
			mEntity = new SharedCLIPtr<Entity>(entity);
			p.X = mEntity->Value->GetPosition().x;
			p.Y = mEntity->Value->GetPosition().y;

		}

		EntityProxy::~EntityProxy()
		{
			delete mEntity;
		}

		LayerProxy^	EntityProxy::Layer::get()
		{
			return mLayer;
		}

		void EntityProxy::Layer::set(LayerProxy^ value)
		{
			mLayer = value;
		}

		String^ EntityProxy::Name::get()
		{
			return gcnew String(mEntity->Value->GetName().c_str());
		}

		Point EntityProxy::Position::get()
		{
			p.X = mEntity->Value->GetPosition().x;
			p.Y = mEntity->Value->GetPosition().y;
			return p;
		}

		void EntityProxy::Position::set(Point value)
		{
			CurrentCommand = gcnew Commands::MoveEntity(this, value) ;//new SetProperty(this, mQuest, "Title", value);
			
			RaisePropertyChanged(this, "Position");

		}

		float EntityProxy::Angle::get()
		{
			return mEntity->Value->GetAngle();
		}

		void EntityProxy::Angle::set(float value)
		{			
			CurrentCommand = gcnew Commands::RotateEntity(this, value) ;//new SetProperty(this, mQuest, "Title", value);

			RaisePropertyChanged(this, "Angle");
			//mEntity->Value->SetAngle(value);
		}

		float EntityProxy::Scale::get()
		{
			return mEntity->Value->GetScale();
		}

		void EntityProxy::Scale::set(float value)
		{
			CurrentCommand = gcnew Commands::ScaleEntity(this, value);

			RaisePropertyChanged(this, "Scale");
		}

		String^ EntityProxy::Type::get()
		{
			return mType;
		}
	}
}