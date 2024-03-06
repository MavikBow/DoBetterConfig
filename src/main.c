#include <windows.h>
#include <stdio.h>
#include "patcher.c"

// Is called by the message loop

LRESULT CALLBACK WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
		case WM_SYSKEYDOWN:
		case WM_KEYDOWN:
		case VK_SNAPSHOT:
			printf(" 0x%x\t%d\t%s\n", (int)wParam, (int)wParam, keyName(wParam));
			return 0;
		case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            // All painting occurs here, between BeginPaint and EndPaint.
            FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));
            EndPaint(hWnd, &ps);
        }
		return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		default:
			return DefWindowProcA(hWnd, uMsg, wParam, lParam);
	}

	return DefWindowProcA(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow)
{
	int window_width = 500;
	int window_height = 500;

	/* these two lines are here to make the compiler shut up about me not using these two variables in the code */
	int useless_int = (int)hPrevInstance | (int)pCmdLine; 
	useless_int ^= 1;

	// Register the window class

	char className[] = "MainWindowClassName";

	WNDCLASSA wc ={0};
	wc.lpfnWndProc = WinProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = className;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;

	if(!RegisterClassA(&wc))
		return -1;

	// Create the window
	
	HWND hWindow = CreateWindowA (
			className, 
			"DoBetterConfig.exe",
		   	WS_MINIMIZEBOX | WS_CAPTION | WS_POPUPWINDOW | WS_SYSMENU,
			(int)((GetSystemMetrics(SM_CXFULLSCREEN) - window_width) >> 1),
			(int)((GetSystemMetrics(SM_CYFULLSCREEN) - window_width) >> 1),
			window_width, window_height,
			HWND_DESKTOP,
			NULL, hInstance, NULL);

	ShowWindow(hWindow, nCmdShow);

	// Run the message loop

	MSG msg;
	while(GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}

	return 0;
}
