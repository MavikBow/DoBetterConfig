#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <windows.h>
#include <commctrl.h>
#include "patcher.h"

#define ID_LISTVIEW 2000

HWND hButton_Menu;
HWND hWndListView;
HINSTANCE g_hInst;

HWND CreateListView(HINSTANCE, HWND);
BOOL InitListView(HWND);
BOOL InsertListViewItems(HWND);

// Is called by the message loop

LRESULT CALLBACK WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
		//case WM_NOTIFY:
		//	HandleWM_NOTIFY(lParam);
		//	break;
		case WM_SYSKEYDOWN:
		case WM_KEYDOWN:
			printf(" 0x%x\t%d\t%s\n", (int)wParam, (int)wParam, keyName(wParam));
			break;
		case WM_CREATE:
			hWndListView = CreateListView(g_hInst, hWnd);

			InitListView(hWndListView);
			break;
		case WM_NCCREATE:
			readInput();
			parseInput();
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProcA(hWnd, uMsg, wParam, lParam);
	}

	return DefWindowProcA(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow)
{
	g_hInst = hInstance;

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
	wc.hbrBackground = (HBRUSH)COLOR_BACKGROUND;

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

HWND CreateListView(HINSTANCE hInstance, HWND hWndParent)
{
	hWndListView = CreateWindowA(
			WC_LISTVIEW,                // class name - defined in commctrl.h
			TEXT(""),
			WS_TABSTOP | WS_CHILD | WS_BORDER | WS_VISIBLE | LVS_REPORT,
			100, 100, 300, 300,
			hWndParent,
			(HMENU)ID_LISTVIEW,
			hInstance, 
			NULL);

	if(!hWndListView) return NULL;

	return hWndListView;
}

BOOL InitListView(HWND hwndListView)
{
	LV_COLUMN lvColumn;
	int i;
	TCHAR szString[2][10] = {TEXT("Action"), TEXT("Key")};

	// empty the list
	ListView_DeleteAllItems(hwndListView);

	// initialize the columns
	lvColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvColumn.fmt = LVCFMT_LEFT;
	lvColumn.cx = 150;

	for(i = 0; i < 2; i++)
	{
		lvColumn.pszText = szString[i];
		ListView_InsertColumn(hwndListView, (WPARAM)i, &lvColumn);
	}

	InsertListViewItems(hwndListView);

	return TRUE;
}

BOOL InsertListViewItems(HWND hwndListView)
{
	// empty the list
	ListView_DeleteAllItems(hwndListView);

	// set the number of the items in the list
	ListView_SetItemCount(hwndListView, 13);

	return TRUE;
}
