#define _WIN32_IE 0x0300				// this and the next line hopefully solve some
#define _WIN32_WINNT 0x0500 			// compatibility issues with older Window versions */
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <windows.h>
#include <wingdi.h>										
#include <commctrl.h>
#include "patcher.h"
#include "resrc/myicon.h"

#define ID_LISTVIEW 2000
#define ID_RESETBUTTON 2001
#define ID_APPLYBUTTON 2002
#define ID_CANCELBUTTON 2003
#define ID_BACKUPCHECKBOX 2004
#define ID_RESETCHECKBOX 2005

HWND hWndListView;
HINSTANCE g_hInst;

BOOL takingControlInput;
int changingControlNumber;

HWND CreateListView(HINSTANCE, HWND);
HWND CreateOtherControls(HWND);
BOOL InitListView(HWND);
BOOL InsertListViewItems(HWND);
void HandleWM_NOTIFY(HWND, LPARAM);
void changingControl(WPARAM);
void resetAll();
int handleApply(HWND);

// Is called by the message loop

LRESULT CALLBACK WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_SYSKEYDOWN:
		case WM_KEYDOWN:
			if(takingControlInput == TRUE)
			{
				changingControl(wParam);
			}
			break;

		case WM_COMMAND:
			if(takingControlInput == TRUE)
			{
				changingControl(wParam);
				break;
			}
			switch(wParam)
			{
				case ID_RESETBUTTON:
					resetAll();
					break;

				case ID_APPLYBUTTON:
					handleApply(hWnd);
					break;

				case ID_CANCELBUTTON:
					DestroyWindow(hWnd);
					break;

				case ID_BACKUPCHECKBOX:
					{
						UINT checked = IsDlgButtonChecked(hWnd, ID_BACKUPCHECKBOX);
						if(checked) CheckDlgButton(hWnd, ID_BACKUPCHECKBOX, BST_UNCHECKED);
						else CheckDlgButton(hWnd, ID_BACKUPCHECKBOX, BST_CHECKED);
					}
					break;

				case ID_RESETCHECKBOX:
					{
						UINT checked = IsDlgButtonChecked(hWnd, ID_RESETCHECKBOX);
						if(checked) CheckDlgButton(hWnd, ID_RESETCHECKBOX, BST_UNCHECKED);
						else CheckDlgButton(hWnd, ID_RESETCHECKBOX, BST_CHECKED);
					}
					break;

				default:
					break;
			}
			break;

		case WM_NOTIFY:
			HandleWM_NOTIFY(hWnd, lParam);
			break;

		case WM_CREATE:
			hWndListView = CreateListView(g_hInst, hWnd);
			CreateOtherControls(hWnd);

			InitListView(hWndListView);
			CheckDlgButton(hWnd, ID_RESETCHECKBOX, BST_CHECKED);
			break;

		case WM_NCCREATE:
			if(readInput() != 0)
			{
				MessageBeep(MB_OK);
				MessageBox(hWnd, "There trouble reading Doukutsu.exe", NULL, MB_OK);
				DestroyWindow(hWnd);
			}
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
	takingControlInput = FALSE;

	int window_width = 460;
	int window_height = 287;

	/* these two lines are here to make the compiler shut up about me not using these two variables in the code */
	int useless_int = (int)hPrevInstance | (int)pCmdLine; 
	useless_int ^= 1;

	// Register the window class

	char className[] = "MainWindowClassName";

	HBRUSH hbr = CreateSolidBrush(RGB(240,240,240));
	HICON hic = LoadIconA(hInstance, MAKEINTRESOURCE(IDI_MYICON));

	WNDCLASSA wc ={0};
	wc.lpfnWndProc = WinProc;
	wc.hInstance = hInstance;
	wc.hIcon = hic;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = className;
	wc.hbrBackground = hbr;

	if(!RegisterClassA(&wc))
		return -1;

	// Create the window
	
	HWND hWindow = CreateWindowA (
			className, 
			"DoBetterConfig.exe",
		   	WS_MINIMIZEBOX | WS_CAPTION | WS_POPUPWINDOW | WS_SYSMENU,
			(int)((GetSystemMetrics(SM_CXFULLSCREEN) - window_width) >> 1),
			(int)((GetSystemMetrics(SM_CYFULLSCREEN) - window_height) >> 1),
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

	DeleteObject(hbr);
	DeleteObject(hic);

	return 0;
}

HWND CreateListView(HINSTANCE hInstance, HWND hWndParent)
{
	hWndListView = CreateWindowA(
			WC_LISTVIEW,                // class name - defined in commctrl.h
			TEXT(""),
			WS_TABSTOP | WS_CHILD | WS_BORDER | WS_VISIBLE | LVS_NOSORTHEADER | LVS_REPORT | LVS_SINGLESEL,
			15, 15, 300, 231,
			hWndParent,
			(HMENU)ID_LISTVIEW,
			hInstance, 
			//NULL,
			//NULL,
			NULL);

	if(!hWndListView) return NULL;

	ListView_SetExtendedListViewStyle(hWndListView, LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE);

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

	LVITEM lvItem;
	TCHAR szString[13][2][30] = {{TEXT("Action 0"),	TEXT("Key 0")},
								{TEXT("Action 1"),	TEXT("Key 1")},
								{TEXT("Action 2"),	TEXT("Key 2")},
								{TEXT("Action 3"),	TEXT("Key 3")},
								{TEXT("Action 4"),	TEXT("Key 4")},
								{TEXT("Action 5"),	TEXT("Key 5")},
								{TEXT("Action 6"),	TEXT("Key 6")},
								{TEXT("Action 7"),	TEXT("Key 7")},
								{TEXT("Action 8"),	TEXT("Key 8")},
								{TEXT("Action 9"),	TEXT("Key 9")},
								{TEXT("Action 10"),	TEXT("Key 10")},
								{TEXT("Action 11"),	TEXT("Key 11")},
								{TEXT("Action 12"),	TEXT("Key 12")}};

	for(int i = 0; i < 13; i++) strcpy(szString[i][0], retrieveKeyName1(i));
	for(int i = 0; i < 13; i++) strcpy(szString[i][1], retrieveKeyName2(i));
	
	// initialize the item
	lvItem.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvItem.stateMask = 0;
	lvItem.iSubItem = 0;
	lvItem.state = 0;

	for(int i = 0; i < 13; i++)
	{
		lvItem.pszText = szString[i][0];
		int Ret = ListView_InsertItem(hwndListView, &lvItem);
		ListView_SetItemText(hwndListView, (WPARAM)Ret, 1, szString[i][1]);
	}

	return TRUE;
}

void HandleWM_NOTIFY(HWND hWnd, LPARAM lParam)
{
	LPNMHDR lpnmh = (LPNMHDR)lParam;
	if(lpnmh->hwndFrom == hWndListView && lpnmh->idFrom == ID_LISTVIEW)
	{
		switch(lpnmh->code)
		{
			case (UINT)NM_CLICK:
			case (UINT)NM_RCLICK:
				{
					int iItem = ListView_GetNextItem(hWndListView, (UINT)-1, LVNI_FOCUSED);
					if(iItem != -1) 
					{
						if(takingControlInput == FALSE)
						{
							// here we handle the input for control button
							takingControlInput = TRUE;
							ListView_SetItemText(hWndListView, (WPARAM)iItem, 1, "<Press any key>");
							changingControlNumber = iItem;
							SetFocus(hWnd);
							break;
						}
						else
							changingControl(0x01);
					}
				}
			break;	
			/*
			case LVN_ITEMCHANGED:
			{
        		NMLISTVIEW* pnmv = (NMLISTVIEW*)lParam;
        		if((pnmv->uChanged & LVIF_STATE) && (pnmv->uNewState & LVIS_SELECTED))
        		{
            		// The item just got selected, do something with it.
            		// pnmv->iItem is the index of the item that was just selected.
					ListView_SetItemState(hWndListView,(UINT)pnmv->iItem, 0, LVIS_SELECTED);
					printf("click %d\n", pnmv->iItem);
        		}
			}
			break;
			*/
		}
	}
}

HWND CreateOtherControls(HWND hWndParent)
{
	HWND hButton_Reset = CreateWindowA(
			WC_BUTTONA,
			"Reset All",
			WS_VISIBLE | WS_CHILD | WS_TABSTOP,
			325, 133, 115, 35,
			hWndParent,
			(HMENU)ID_RESETBUTTON,
			NULL,
			NULL);

	if(!hButton_Reset) return NULL;

	HWND hButton_Apply = CreateWindowA(
			WC_BUTTONA,
			"Apply",
			WS_VISIBLE | WS_CHILD | WS_TABSTOP,
			325, 172, 115, 35,
			hWndParent,
			(HMENU)ID_APPLYBUTTON,
			NULL,
			NULL);

	if(!hButton_Apply) return NULL;

	HWND hButton_Cancel = CreateWindowA(
			WC_BUTTONA,
			"Cancel",
			WS_VISIBLE | WS_CHILD | WS_TABSTOP,
			325, 211, 115, 35,
			hWndParent,
			(HMENU)ID_CANCELBUTTON,
			NULL,
			NULL);

	if(!hButton_Cancel) return NULL;

	HWND hCheckBox_BackupDoukutsu = CreateWindowA(
			WC_BUTTONA,
			"Backup Doukutsu.exe",
			WS_VISIBLE | WS_CHILD | BS_CHECKBOX | BS_MULTILINE | WS_TABSTOP,
			325, 25, 115, 40,
			hWndParent,
			(HMENU)ID_BACKUPCHECKBOX,
			NULL,
			NULL);

	if(!hCheckBox_BackupDoukutsu) return NULL;

	HWND hCheckBox_ResetCondig = CreateWindowA(
			WC_BUTTONA,
			"Reset Config.dat",
			WS_VISIBLE | WS_CHILD | BS_CHECKBOX | BS_MULTILINE | WS_TABSTOP,
			325, 70, 115, 40,
			hWndParent,
			(HMENU)ID_RESETCHECKBOX,
			NULL,
			NULL);

	if(!hCheckBox_ResetCondig) return NULL;

	return hButton_Reset;
}

void changingControl(WPARAM wParam)
{
	TCHAR temp[30];
	int success = uploadKey(wParam, changingControlNumber);

	if(success == 0)
		strcpy(temp, keyName(wParam));
	else
	{
		strcpy(temp, retrieveKeyName2(changingControlNumber));
		MessageBeep(MB_OK);
	}

	ListView_SetItemText(hWndListView, (WPARAM)changingControlNumber, 1, temp);
	takingControlInput = FALSE;
}

void resetAll()
{
	TCHAR temp[30];
	for(int i = 0; i < 13; i++)
	{
		strcpy(temp, retrieveKeyName2Default(i));
		ListView_SetItemText(hWndListView, (WPARAM)i, 1, temp);
	}
	resetLayout();
}

int handleApply(HWND hWnd)
{
	UINT checked;
	checked = IsDlgButtonChecked(hWnd, ID_BACKUPCHECKBOX);
	if(checked) 
	{
		if(backUpDoukutsu() != 0)
		{
			MessageBeep(MB_OK);
			MessageBox(hWnd, "There was trouble with performing a backup", NULL, MB_OK);
			return -1;
		}
	}
	checked = IsDlgButtonChecked(hWnd, ID_RESETCHECKBOX);
	if(checked)	
	{
		if(resetConfig() != 0)
		{
			MessageBeep(MB_OK);
			MessageBox(hWnd, "There was trouble with reading Config.dat", NULL, MB_OK);
			return -1;
		}
	}

	if(applyFinalLayout() != 0)
	{
		MessageBeep(MB_OK);
		MessageBox(hWnd, "There was trouble with writing into Doukutsu.exe", NULL, MB_OK);
		return -1;
	}

	return 0;
}
