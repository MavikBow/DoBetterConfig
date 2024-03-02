#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <windows.h>

LRESULT CALLBACK WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
		case WM_PAINT:
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		default:
			return DefWindowProcA(hWnd, uMsg, wParam, lParam);
	}

	return DefWindowProcA(hWnd, uMsg, wParam, lParam);
	return 0;
}

int32_t WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int32_t nCmdShow)
{
	/* these two lines are just here to make the compiler shut up about me not using these four parameters in the code */
	int32_t useless_int = (int32_t)hInstance | (int32_t)hPrevInstance | (int32_t)pCmdLine | nCmdShow; 
	useless_int ^= 1;

	/* IMPORTANT: I'm putting the name into a separate string because
	 * it is CRUTIAL that the name in WNDCLASSA and CreateWindowA are the exact same.
	 * Otherwise it will create an invisible process that you will need to manually stop
	 * in the task manager. And until you do that you won't be able to compile this code,
	 * nor delete the already existing executable file */
	char* className = "MainWindowClassName";

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

	HWND hWindow = CreateWindowA(className, "Hi mom", WS_CAPTION | WS_POPUP | WS_SYSMENU, 50, 50, 500, 500, NULL, NULL, hInstance, NULL);

	ShowWindow(hWindow, nCmdShow);

	MSG msg;
	while(GetMessage(&msg, NULL, 0, 0) > 0)
	{
		DispatchMessageA(&msg);
	}

	return 0;
}
