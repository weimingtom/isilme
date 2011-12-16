#pragma  once
using namespace System;
using namespace System::Windows;
using namespace System::Windows::Input;
using namespace Common;
using namespace Common::Views;

namespace LevelEditor
{
	namespace Views
	{
		public ref class LevelEditorWindow : public EditorWindow
		{
		public:
			LevelEditorWindow();

		private:
			void OnMouseDown(Object^ sender, MouseButtonEventArgs^ e);

			void OnMouseUp(Object^ sender, MouseButtonEventArgs^ e);

			IntPtr ControlMsgFilter(IntPtr hwnd, int msg, IntPtr wParam, IntPtr lParam, bool% handled);

			IntPtr^ mHandle;

			void OnFrameUpdate(float elapsedTime);
		};
	}
}