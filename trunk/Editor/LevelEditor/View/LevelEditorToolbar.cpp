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
			// ����� ��������
			System::Windows::Controls::RadioButton^ mBrushToolBtn = gcnew RadioButton();
			mBrushToolBtn->Content = "Brush";
			mBrushToolBtn->Command = LevelEditorWindow::SelectEntityBrush;

			// �������� ����
			System::Windows::Controls::Button^ mAddLayerBtn = gcnew Button();
			mAddLayerBtn->Content = "Layer";
			mAddLayerBtn->Command = LevelEditorWindow::AddLayerCommand;

			// �������� �����
			System::Windows::Controls::CheckBox^ mActivateGridBtn = gcnew CheckBox();
			mActivateGridBtn->Content = "Grid";
			mActivateGridBtn->Command = LevelEditorCommands::ActivateGrid;

			// ����� ��������
			System::Windows::Controls::RadioButton^ mSelectorBtn = gcnew RadioButton();
			mSelectorBtn->Content = "Select";
			mSelectorBtn->Command = LevelEditorCommands::SelectObjectsSelector;

			// ��������� ������
			CheckBox^ mTurnPhisics = gcnew CheckBox();
			mTurnPhisics->Content = "Phisics";
			mTurnPhisics->Command = LevelEditorCommands::ActivatePhisics;

			CheckBox^ mDrawPhisics = gcnew CheckBox();
			mDrawPhisics->Content = "Draw Phisics";
			mDrawPhisics->Command = LevelEditorCommands::DrawPhisics;

			// ��������� ������
			AddChild(mBrushToolBtn);
			AddChild(mSelectorBtn);
			AddChild(mAddLayerBtn);
			AddChild(mActivateGridBtn);
			AddChild(mTurnPhisics);
			AddChild(mDrawPhisics);
		}

	}
}