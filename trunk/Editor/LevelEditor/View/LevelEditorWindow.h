#pragma  once

#include "../Tool/EntityBrush.h"

using namespace System;
using namespace System::Windows;
using namespace System::Windows::Input;
using namespace Common;
using namespace Common::Views;
using namespace LevelEditor::Tool;

namespace LevelEditor
{
	namespace View
	{
		public ref class LevelEditorWindow : public EditorWindow
		{
		public:
			LevelEditorWindow();

			static RoutedCommand^ SelectEntityBrush = gcnew RoutedCommand();
			static RoutedCommand^ SelectSelectorTool = gcnew RoutedCommand();
			static RoutedCommand^ AddLayerCommand = gcnew RoutedCommand();

			property LevelProxy^ Level
			{
				LevelProxy^ get();
			}
		private:

			///< Редактируемый уровень
			LevelProxy^ mLevel;

			void OnMouseDown(Object^ sender, MouseButtonEventArgs^ e);

			void OnMouseUp(Object^ sender, MouseButtonEventArgs^ e);

			IntPtr ControlMsgFilter(IntPtr hwnd, int msg, IntPtr wParam, IntPtr lParam, bool% handled);

			IntPtr^ mHandle;

			void OnFrameUpdate(float elapsedTime);

			///< Текущий инструмент
			ITool^ mCurrentBrush;

			///< Кисть объектов
			EntityBrush^ mEntityBrush;


			void ExecutedSelectEntityBrush(Object^ sender, ExecutedRoutedEventArgs^ e);

			void CanExecuteSelectEntityBrush(System::Object^ sender, System::Windows::Input::CanExecuteRoutedEventArgs^ e);

			void ExecutedAddLayer(Object^ sender, ExecutedRoutedEventArgs^ e);

			void CanExecuteAddLayer(System::Object^ sender, System::Windows::Input::CanExecuteRoutedEventArgs^ e);
		};
	}
}