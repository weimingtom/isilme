#ifndef _HIDDEN_WINDOW_H_INCLUDED_
#define _HIDDEN_WINDOW_H_INCLUDED_

#include "windows.h"

HWND CreateHiddenWindow(void);  				   // �������� �������� ����
void ReleaseHiddenWindow(HWND window);  		   // �������� �������� ����

#endif