#include "Stdafx.h"
#include "LevelEditorToolbar.h"
#include "LevelEditorWindow.h"
#include "../LevelEditorCommands.h"
#include "../ResourceHelper.h"

namespace LevelEditor
{
	namespace View
	{
		LevelEditorToolBar::LevelEditorToolBar()
		{
			System::Windows::Controls::Image^ image;
			// Кисть объектов
			System::Windows::Controls::RadioButton^ mBrushToolBtn = gcnew RadioButton();
			image = gcnew System::Windows::Controls::Image();
			image->Source = ResourceHelper::GetPngSource("Brush.png");
			image->Width = 24;
			image->Height = 24;
			mBrushToolBtn->Content = image;
			mBrushToolBtn->Command = LevelEditorWindow::SelectEntityBrush;
			mBrushToolBtn->ToolTip = "Entity brush";

			// Добавить слой
			System::Windows::Controls::Button^ mAddLayerBtn = gcnew Button();
			image = gcnew System::Windows::Controls::Image();
			image->Source = ResourceHelper::GetPngSource("AddLayer.png");
			image->Width = 24;
			image->Height = 24;
			mAddLayerBtn->Content = image;
			mAddLayerBtn->Command = LevelEditorWindow::AddLayerCommand;
			mAddLayerBtn->ToolTip = "Add layer";

			// Включить сетку
			System::Windows::Controls::CheckBox^ mActivateGridBtn = gcnew CheckBox();
			image = gcnew System::Windows::Controls::Image();
			image->Source = ResourceHelper::GetPngSource("Grid.png");
			image->Width = 24;
			image->Height = 24;
			mActivateGridBtn->Content = image;
			mActivateGridBtn->Command = LevelEditorCommands::ActivateGrid;
			mActivateGridBtn->ToolTip = "Snap to grid";

			// Выбор объектов
			System::Windows::Controls::RadioButton^ mSelectorBtn = gcnew RadioButton();
			image = gcnew System::Windows::Controls::Image();
			image->Source = ResourceHelper::GetPngSource("Select.png");
			image->Width = 24;
			image->Height = 24;
			mSelectorBtn->Content = image;
			mSelectorBtn->Command = LevelEditorCommands::SelectObjectsSelector;
			mSelectorBtn->ToolTip = "Select entity";

			// Включение физики
			CheckBox^ mTurnPhisics = gcnew CheckBox();
			image = gcnew System::Windows::Controls::Image();
			image->Source = ResourceHelper::GetPngSource("Physics.png");
			image->Width = 24;
			image->Height = 24;
			mTurnPhisics->Content = image;
			mTurnPhisics->Command = LevelEditorCommands::ActivatePhisics;
			mTurnPhisics->ToolTip = "Physics";

			CheckBox^ mDrawPhisics = gcnew CheckBox();
			image = gcnew System::Windows::Controls::Image();
			image->Source = ResourceHelper::GetPngSource("Shapes.png");
			image->Width = 24;
			image->Height = 24;
			mDrawPhisics->Content = image;
			mDrawPhisics->Command = LevelEditorCommands::DrawPhisics;
			mDrawPhisics->ToolTip = "Draw physics";

			// Добавляем кнопки
			AddChild(mBrushToolBtn);
			AddChild(mSelectorBtn);
			AddChild(mAddLayerBtn);
			AddChild(mActivateGridBtn);
			AddChild(mTurnPhisics);
			AddChild(mDrawPhisics);
		}

	}
}