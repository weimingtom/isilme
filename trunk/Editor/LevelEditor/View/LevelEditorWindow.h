#pragma  once

#include "../Tool/EntityBrush.h"

using namespace System;
using namespace System::Windows;
using namespace System::Windows::Input;
using namespace Common;
using namespace Common::Views;
using namespace LevelEditor::Tool;
using namespace System::Collections::Generic;

namespace LevelEditor
{
	ref class IsilmeHost;
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

			virtual void OnClosing(System::ComponentModel::CancelEventArgs^ e) override;
		private:

			Dictionary<String^, LevelProxy^>^ mLoadedLevels;

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

			///< Выделение объектов
			SelectorTool^ mObjectsSelector;

			int mOldMouseX;
			int mOldMouseY;
			LevelEditor::IsilmeHost^ host;
			System::Windows::Controls::Border^ mBorder;
			void ExecutedSelectEntityBrush(Object^ sender, ExecutedRoutedEventArgs^ e);
			void CanExecuteSelectEntityBrush(System::Object^ sender, System::Windows::Input::CanExecuteRoutedEventArgs^ e);
			void ExecutedSelectEntityBrush(Object^ param);
			bool CanExecuteSelectEntityBrush();

			void ExecutedSelectObjectsSelector(Object^ param);
			bool CanExecuteSelectObjectsSelector();

			void ExecutedActivatePhisics(Object^ param);
			bool CanExecuteActivatePhisics();

			void ExecutedDrawPhisics(Object^ param);
			bool CanExecuteDrawPhisics();

			void ExecutedAddLayer(Object^ sender, ExecutedRoutedEventArgs^ e);
			void CanExecuteAddLayer(System::Object^ sender, System::Windows::Input::CanExecuteRoutedEventArgs^ e);

			void ExecutedSelectPaletteItem(Object^ sender, ExecutedRoutedEventArgs^ e);
			void CanExecuteSelectPaletteItem(System::Object^ sender, System::Windows::Input::CanExecuteRoutedEventArgs^ e);

			void ExecutedRemoveEntity(Object^ sender, ExecutedRoutedEventArgs^ e);
			void CanExecuteRemoveEntity(System::Object^ sender, System::Windows::Input::CanExecuteRoutedEventArgs^ e);

			void ExecutedCopyEntity(Object^ sender, ExecutedRoutedEventArgs^ e);
			void CanExecuteCopyEntity(System::Object^ sender, System::Windows::Input::CanExecuteRoutedEventArgs^ e);

			void ExecutedPasteEntity(Object^ sender, ExecutedRoutedEventArgs^ e);
			void CanExecutePasteEntity(System::Object^ sender, System::Windows::Input::CanExecuteRoutedEventArgs^ e);
		};
	}
}