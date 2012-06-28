#include <windows.h>

// �������� ����
HWND CreateHiddenWindow(void)
{
	WNDCLASS wc;

	wc.style = 0;
	wc.lpfnWndProc = DefWindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetModuleHandle(NULL);
	wc.hIcon = NULL;
	wc.hCursor = NULL;
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "SquallHiddenWindow";
	RegisterClass(&wc);

	// �������� ������� ����
	return CreateWindow("SquallHiddenWindow",
		   	"",
		   	WS_POPUP,
		   	0,
		   	0,
		   	0,
		   	0,
		   	NULL,
		   	NULL,
		   	GetModuleHandle(NULL),
		   	NULL);
}

// �������� �������� ����
void ReleaseHiddenWindow(HWND window)
{
	if (window)
		DestroyWindow(window);
}