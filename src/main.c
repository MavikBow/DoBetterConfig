#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <windows.h>

LRESULT CALLBACK WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
		case WM_CREATE:
			
		break;
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

int32_t WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int32_t nCmdShow)
{
	/* these two lines are just here to make the compiler shut up about me not using these four parameters in the code */
	int32_t useless_int = (int32_t)hInstance | (int32_t)hPrevInstance | (int32_t)pCmdLine | nCmdShow; 
	useless_int ^= 1;

	// Register the window class

	/* IMPORTANT: it's CRUTIAL for the name in WNDCLASSA and CreateWindowA to match.
	 * Otherwise an invisible process is created that must be manually stopped
	 * in the task manager. And until you do that further compilation of this code
	 * and deletion of the already existing executable file isn't feasible */
	char className[] = "MainWindowClassName";

	WNDCLASSA class = {
		0,
		WinProc,
		0,
		0,
		hInstance,
		NULL,
		NULL,
		NULL,
		NULL,
		className
	};

	RegisterClassA(&class);

	// Create the window

	HWND hWindow = CreateWindowA (
			className, 
			"DoBetterConfig.exe",
		   	WS_MINIMIZEBOX | WS_CAPTION | WS_POPUPWINDOW | WS_SYSMENU,
		   	(int)CW_USEDEFAULT,
		   	(int)CW_USEDEFAULT,
			500, 500,
			HWND_DESKTOP,
			NULL, hInstance,NULL);

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
