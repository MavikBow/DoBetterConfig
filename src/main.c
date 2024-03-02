#include <windows.h>

// Is called by the message loop

LRESULT CALLBACK WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
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
	/* these two lines are here to make the compiler shut up about me not using these two variables in the code */
	int useless_int = (int)hPrevInstance | (int)pCmdLine; 
	useless_int ^= 1;

	// Register the window class

	/* IMPORTANT: it's crutial for the name in WNDCLASSA and CreateWindowA to match.
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
