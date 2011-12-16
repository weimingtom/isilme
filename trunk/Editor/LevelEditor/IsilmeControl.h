#pragma once

namespace LevelEditor
{
	using namespace System;
	using namespace System::Windows;
	using namespace System::Windows::Interop;
	using namespace System::Windows::Input;
	using namespace System::Windows::Media;
	using namespace System::Runtime::InteropServices;

	public delegate void UpdateFrameHandler(float elapsedTime);

	public ref class IsilmeHost : public System::Windows::Interop::HwndHost
	{
	private:
		HWND dialog;
	public:
		IsilmeHost();

		void Start();

		void OnThreadIdle(Object^ sender, EventArgs^ e);
		virtual HandleRef BuildWindowCore(HandleRef hwndParent) override;
		virtual void DestroyWindowCore(HandleRef hwndParent) override;
		virtual IntPtr WndProc(
			IntPtr hwnd,
			int msg,
			IntPtr wParam,
			IntPtr lParam,
			bool handled
			) override;

		void OnUpdate(float elapsedTime);

		UpdateFrameHandler^ UpdateFrame;
	};
};