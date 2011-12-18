#include "../Stdafx.h"

using namespace System;
using namespace System::Windows;
using namespace System::Windows::Controls;
using namespace System::Windows::Data;
using namespace System::Windows::Input;
using namespace LevelEditor::Proxy;

namespace LevelEditor
{
	namespace View
	{
		public ref class EntityPaletteTool : public Common::Views::ToolWindow//, public ICommandSource
		{
		public:
			//static DependencyProperty^ CommandProperty =
			//	DependencyProperty::Register(
			//	"Command",
			//	System::Windows::Input::ICommand::typeid,
			//	EntityPaletteTool::typeid,
			//	gcnew PropertyMetadata((System::Windows::Input::ICommand^)nullptr,
			//	gcnew PropertyChangedCallback(&EntityPaletteTool::CommandChanged)));

			virtual ~EntityPaletteTool();

			static property EntityPaletteTool^ Instance
			{
				EntityPaletteTool^ get();
			}

			property EntityPaletteProxy^ Palette
			{
				EntityPaletteProxy^ get();
				void set(EntityPaletteProxy^ value);
			}

			property PaletteItemProxy^ SelectedItem
			{
				PaletteItemProxy^ get();
			}

			//property System::Windows::Input::ICommand^ Command
			//{
			//	virtual System::Windows::Input::ICommand^ get();
			//	virtual void set(System::Windows::Input::ICommand^ value);
			//}

			//property Object^ CommandParameter
			//{
			//	virtual Object^ get();
			//}

			//property System::Windows::IInputElement^ CommandTarget
			//{
			//	virtual 	 System::Windows::IInputElement^ get();
			//}
		protected:
			EntityPaletteTool();

			void OnItemSelected(Object^ sender, MouseButtonEventArgs^ e);
		private:
			PaletteItemProxy^ mCurrentItem;
			EntityPaletteProxy^ mPalette;
			TreeView^ mPaletteTree;
			static EntityPaletteTool^ mInstance;
			//EventHandler^ canExecuteChangedHandler;
			//static void CommandChanged(DependencyObject^ d, DependencyPropertyChangedEventArgs e);
			//void HookUpCommand( System::Windows::Input:: ICommand^ oldValue,  System::Windows::Input::ICommand^ newValue );
			//void AddCommand( System::Windows::Input::ICommand^ oldCommand,  System::Windows::Input::ICommand^ newCommand );
			//void RemoveCommand(  System::Windows::Input::ICommand^ oldCommand,  System::Windows::Input::ICommand^ newCommand );
			//void CanExecuteChanged(Object^ sender, EventArgs^ e);
		};
	}
}