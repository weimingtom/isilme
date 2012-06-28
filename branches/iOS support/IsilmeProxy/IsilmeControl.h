#pragma once

namespace IsilmeProxy
{
	using namespace System;
	using namespace System::Windows;
	using namespace System::Windows::Interop;
	using namespace System::Windows::Input;
	using namespace System::Windows::Media;
	using namespace System::Runtime::InteropServices;

	public ref class IsilmeHost : public System::Windows::Interop::HwndHost
	{
	private:
		HWND dialog;
	public:
		IsilmeHost();

		void Start();
		virtual HandleRef BuildWindowCore(HandleRef hwndParent) override;
		virtual void DestroyWindowCore(HandleRef hwndParent) override;
		virtual IntPtr WndProc(
			IntPtr hwnd,
			int msg,
			IntPtr wParam,
			IntPtr lParam,
			bool handled
			) override;
	};
};