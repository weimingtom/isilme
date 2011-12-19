#include "Stdafx.h"
#include "LevelEditorToolbar.h"
#include "LevelEditorWindow.h"
#include "../LevelEditorCommands.h"

namespace LevelEditor
{
	namespace View
	{
		LevelEditorToolBar::LevelEditorToolBar()
		{
			// Кисть объектов
			System::Windows::Controls::Button^ mBrushToolBtn = gcnew Button();
			mBrushToolBtn->Content = "Brush";
			mBrushToolBtn->Command = LevelEditorWindow::SelectEntityBrush;

			// Добавить слой
			System::Windows::Controls::Button^ mAddLayerBtn = gcnew Button();
			mAddLayerBtn->Content = "Layer";
			mAddLayerBtn->Command = LevelEditorWindow::AddLayerCommand;

			// Включить сетку
			System::Windows::Controls::CheckBox^ mActivateGridBtn = gcnew CheckBox();
			mActivateGridBtn->Content = "Grid";
			mActivateGridBtn->Command = LevelEditorWindow::ActivateGrid;

			// Выбор объектов
			System::Windows::Controls::Button^ mSelectorBtn = gcnew Button();
			mSelectorBtn->Content = "Select";
			mSelectorBtn->Command = LevelEditorCommands::SelectObjectsSelector;

			// Добавляем кнопки
			AddChild(mBrushToolBtn);
			AddChild(mSelectorBtn);
			AddChild(mAddLayerBtn);
			AddChild(mActivateGridBtn);
		}

	}
}