#include "Stdafx.h"
#include "LevelEditorToolbar.h"
#include "LevelEditorWindow.h"

namespace LevelEditor
{
	namespace View
	{
		LevelEditorToolBar::LevelEditorToolBar()
		{
			// ����� ��������
			System::Windows::Controls::Button^ mBrushToolBtn = gcnew Button();
			mBrushToolBtn->Content = "Brush";
			mBrushToolBtn->Command = LevelEditorWindow::SelectEntityBrush;

			// �������� ����
			System::Windows::Controls::Button^ mAddLayerBtn = gcnew Button();
			mAddLayerBtn->Content = "Layer";
			mAddLayerBtn->Command = LevelEditorWindow::AddLayerCommand;

			// ��������� ������
			AddChild(mBrushToolBtn);
			AddChild(mAddLayerBtn);
		}

	}
}