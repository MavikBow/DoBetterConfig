#include <windows.h>
#include <commctrl.h>
#include "patcher.h"

HWND hButton_Menu;
HWND hWndListView;
typedef struct PETINFO
        {
            TCHAR szKind[10];
            TCHAR szBreed[50];
            TCHAR szPrice[20];
        }PETINFO;

        struct PETINFO rgPetInfo[ ] = 
        {
            {TEXT("Dog"),  TEXT("Poodle"),     TEXT("$300.00")},
            {TEXT("Cat"),  TEXT("Siamese"),    TEXT("$100.00")},
            {TEXT("Fish"), TEXT("Angel Fish"), TEXT("$10.00")},
            {TEXT("Bird"), TEXT("Parakeet"),   TEXT("$5.00")},
            {TEXT("Toad"), TEXT("Woodhouse"),  TEXT("$0.25")},
        };
void AddMenus(HWND);

// Is called by the message loop

LRESULT CALLBACK WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
		case WM_NOTIFY:
			HandleWM_NOTIFY(lParam);

			break;

		case WM_SYSKEYDOWN:
		case WM_KEYDOWN:
			printf(" 0x%x\t%d\t%s\n", (int)wParam, (int)wParam, keyName(wParam));
			break;
		case WM_CREATE:
			AddMenus(hWnd);
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

BOOL InsertListViewItems(HWND hWndListView, int cItems)
{
    LVITEM lvI;

    // Initialize LVITEM members that are common to all items.
    lvI.pszText   = LPSTR_TEXTCALLBACK; // Sends an LVN_GETDISPINFO message.
    lvI.mask      = LVIF_TEXT | LVIF_IMAGE |LVIF_STATE;
    lvI.stateMask = 0;
    lvI.iSubItem  = 0;
    lvI.state     = 0;

    // Initialize LVITEM members that are different for each item.
    for (int index = 0; index < cItems; index++)
    {
        lvI.iItem  = index;
        lvI.iImage = index;
    
        // Insert items into the list.
        if (ListView_InsertItem(hWndListView, &lvI) == -1)
            return FALSE;
    }

    return TRUE;
}
void HandleWM_NOTIFY(LPARAM lParam)
{
    NMLVDISPINFO* plvdi;

    switch (((LPNMHDR) lParam)->code)
    {
        case LVN_GETDISPINFO:

            plvdi = (NMLVDISPINFO*)lParam;

            switch (plvdi->item.iSubItem)
            {
                case 0:
                    plvdi->item.pszText = rgPetInfo[plvdi->item.iItem].szKind;
                    break;
                      
                case 1:
                    plvdi->item.pszText = rgPetInfo[plvdi->item.iItem].szBreed;
                    break;
                
                case 2:
                    plvdi->item.pszText = rgPetInfo[plvdi->item.iItem].szPrice;
                    break;
                
                default:
                    break;
            }

        break;

    }
	return;
}	
void AddMenus(HWND hWnd)
{
	//InitCommonControls();
	hWndListView = CreateWindowA(WC_LISTVIEW, 
                                     "",
                                     WS_CHILD | WS_VISIBLE | LVS_LIST,
                                     100, 100,
                                     300,
                                     300,
                                     hWnd,
									 NULL,
                                     //(HMENU)IDM_CODE_SAMPLES,
                                     //g_hInst,
									 NULL,
                                     NULL); 
	InsertListViewItems(hWndListView, 2);
}
