#include "Stdafx.h"
#include "Tool.h"
#include "MouseData.h"
#include "..\SharedCLIPtr.h"
#include "..\Proxy\LayerProxy.h"
#include "..\Proxy\EntityProxy.h"
#include "..\LevelEditorCommands.h"

namespace LevelEditor
{
	namespace Tool
	{
		LayerProxy^ LayerTool::Layer::get()
		{
			return mLayer;
		}

		void LayerTool::Layer::set(LayerProxy^ value)
		{
			mLayer = value;
		}

		void LayerTool::OnMouseUp( MouseData^ mouse )
		{

		}

		void LayerTool::OnMouseDown( MouseData^ mouse )
		{

		}

		void LayerTool::OnMouseMove( MouseData^ mouse )
		{

		}

		Proxy::Point^ LayerTool::ProcessToLevelCoords( MouseData^ mouse )
		{
			Vector2 position(mouse->x, mouse->y);

			position.x /= 64;
			position.y /= 64;

			LayerProxy^ layer = Layer;
			SharedCLIPtr<::Layer>* lp = Layer->mLayer;
			LayerPtr nativeLayer = lp->Value;
			LevelPtr nativeLevel = nativeLayer->GetLevel();

			position.x += layer->mLayer->Value->GetLevel()->GetActiveCamera()->x;
			position.y += layer->mLayer->Value->GetLevel()->GetActiveCamera()->y;

			if (UseGrid)
			{
				int n = position.x / Layer->Grid->Step;
				float x = n * Layer->Grid->Step;

				n = position.y / Layer->Grid->Step;
				float y = n * Layer->Grid->Step;

				position.Set(x,y);
			}

			Proxy::Point^ p = gcnew Proxy::Point();
			p->X = position.x;
			p->Y = position.y;
			return p;
		}

		Proxy::Point^ LayerTool::ProcessToLevelCoordsNoGrid( MouseData^ mouse )
		{
			Vector2 position(mouse->x, mouse->y);

			position.x /= 64;
			position.y /= 64;

			LayerProxy^ layer = Layer;
			SharedCLIPtr<::Layer>* lp = Layer->mLayer;
			LayerPtr nativeLayer = lp->Value;
			LevelPtr nativeLevel = nativeLayer->GetLevel();

			position.x += layer->mLayer->Value->GetLevel()->GetActiveCamera()->x;
			position.y += layer->mLayer->Value->GetLevel()->GetActiveCamera()->y;
			
			Proxy::Point^ p = gcnew Proxy::Point();
			p->X = position.x;
			p->Y = position.y;
			return p;
		}

		LayerTool::LayerTool()
		{
			mUseGrid = false;
			LevelEditorCommands::ActivateGrid->CanExecuteTargets += gcnew System::Func<Boolean>(this, &LayerTool::CanExecuteActivateGrid);
			LevelEditorCommands::ActivateGrid->ExecuteTargets += gcnew System::Action<Object^>(this, &LayerTool::ExecutedActivateGrid);
		}

		bool LayerTool::CanExecuteActivateGrid()
		{
			return true;
		}

		void LayerTool::ExecutedActivateGrid( Object^ param )
		{
			UseGrid = !UseGrid;
		}

		bool LayerTool::UseGrid::get()
		{
			return mUseGrid;
		}

		void LayerTool::UseGrid::set(bool value)
		{
			mUseGrid = value;
		}

	}
}