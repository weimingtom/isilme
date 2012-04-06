#pragma once

#include "../Stdafx.h"

using namespace System;
using namespace System::Windows;
using namespace System::Windows::Controls;
using namespace System::Windows::Input;

namespace LevelEditor
{
	namespace View
	{
		public ref class ObjectManager : public Common::Views::ToolWindow
		{
		public:
			static property ObjectManager^ Instance
			{
				ObjectManager^ get();
			}


			property LevelEditorWindow^ Editor
			{
				LevelEditorWindow^ get();
				void set(LevelEditorWindow^ value);
			}
		protected:
			ObjectManager();

		private:

			///< Текущий редактор уровня
			LevelEditorWindow^ mEditor;

			///< Дерево объектов
			TreeView^ mObjectsTree;

			void OnObjectSelected(Object^ sender, MouseButtonEventArgs^ e);

			static ObjectManager^ mInstance;

			void ExecutedRemove( Object^ sender, ExecutedRoutedEventArgs^ e );

			void CanExecuteRemove( Object^ sender, CanExecuteRoutedEventArgs^ e );

			void OnLevelLoaded(Object^ sender, EventArgs^ e);
		};
	}
}