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

			static Common::DelegateCommand^ SelectEntityBrush = gcnew Common::DelegateCommand();
			static RoutedCommand^ SelectSelectorTool = gcnew RoutedCommand();
			static RoutedCommand^ AddLayerCommand = gcnew RoutedCommand();
			static RoutedCommand^ SelectPaletteItem = gcnew RoutedCommand();
			static RoutedCommand^ ActivateGrid = gcnew RoutedCommand();

			property LevelProxy^ Level
			{
				LevelProxy^ get();
			}

			property LayerProxy^ Layer
			{
				LayerProxy^ get();
				void set(LayerProxy^ value);
			}

			property static LevelEditorWindow^ Instance
			{
				LevelEditorWindow^ get();
			}

			virtual void Load() override;

			virtual void Save() override;
		private:
			bool mNeedToLoad;
			static LevelEditorWindow^ mInstance;

			///< Редактируемый уровень
			LevelProxy^ mLevel;

			LayerProxy^ mLayer;

			void OnMouseDown(Object^ sender, MouseButtonEventArgs^ e);

			void OnMouseUp(Object^ sender, MouseButtonEventArgs^ e);

			IntPtr ControlMsgFilter(IntPtr hwnd, int msg, IntPtr wParam, IntPtr lParam, bool% handled);

			IntPtr^ mHandle;

			void OnFrameUpdate(float elapsedTime);

			///< Текущий инструмент
			ITool^ mCurrentBrush;

			///< Кисть объектов
			EntityBrush^ mEntityBrush;

			///< Скроллер уровня
			ScrollerTool^ mScrollTool;

			int mOldMouseX;
			int mOldMouseY;
			void ExecutedSelectEntityBrush(Object^ sender, ExecutedRoutedEventArgs^ e);
			void CanExecuteSelectEntityBrush(System::Object^ sender, System::Windows::Input::CanExecuteRoutedEventArgs^ e);
			void ExecutedSelectEntityBrush(Object^ param);
			bool CanExecuteSelectEntityBrush();

			void ExecutedAddLayer(Object^ sender, ExecutedRoutedEventArgs^ e);
			void CanExecuteAddLayer(System::Object^ sender, System::Windows::Input::CanExecuteRoutedEventArgs^ e);

			void ExecutedSelectPaletteItem(Object^ sender, ExecutedRoutedEventArgs^ e);
			void CanExecuteSelectPaletteItem(System::Object^ sender, System::Windows::Input::CanExecuteRoutedEventArgs^ e);

			void ExecutedActivateGrid(Object^ sender, ExecutedRoutedEventArgs^ e);
			void CanExecuteActivateGrid(System::Object^ sender, System::Windows::Input::CanExecuteRoutedEventArgs^ e);
		};
	}
}