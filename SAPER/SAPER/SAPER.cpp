// SAPER.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "SAPER.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
int width = 0;
int high = 0;
int countofmins = 0;
int *flaga;
int *mins;
HWND parent;
bool ResetWindow;
int NCS;
const int bufSize = 256;
TCHAR buf[bufSize];
bool TrybDebug;
bool bomba;
// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    CustomSize(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SAPER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SAPER));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SAPER));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SAPER);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}
void unveilF(int f)
{
	for (int i = f - 1; i <= f + 1; i++)
		for (int j = f / 10 - 1; j <= f / 10 + 1; j++)
			if (i >= 0 && i <= 9 && j >= 0 && j <= 9)
				if (j * 10 + i != f)
					if (mins[j * 10 + i] == 0)
						unveilF(j * 10 + i);
	flaga[f] = 2;

}
void GetTextInfoForKeyMsg(WPARAM wParam, TCHAR *msgName, TCHAR *buf, int bufSize)
{
	static int sjcounter = 0;
	static int sdcounter = 0;
	static int mjcounter = 0;
	static int mdcounter = 0;
	if (sjcounter == 9)
	{
		if (sdcounter == 5)
		{
			if (mjcounter == 9)
			{
				mjcounter = 0;
				mdcounter++;
			}
			else
				mjcounter++;
			sdcounter = 0;
		}
		else
			sdcounter++;
		sjcounter = 0;
	}
	else
		sjcounter++;
	_stprintf_s(buf, bufSize, _T("Miny: %d T:%d%d:%d%d"), countofmins, mdcounter, mjcounter, sdcounter, sjcounter);
}
void FillMins()
{
	int *fillmins = (int*)malloc(sizeof(int)*(width + 2)*(high + 2));
	mins = (int*)malloc(sizeof(int)*width*high);
	for (int i = 0; i < high + 2; i++)
		for (int j = 0; j < width + 2; j++)
			fillmins[i*(width + 2) + j] = 0;
	for (int i = 0; i < high; i++)
		for (int j = 0; j < width; j++)
			mins[i * width + j] = 0;
	int poziom = 1 + rand() % high;
	int pion = 1 + rand() % width;
	for (int i = 0; i < countofmins; i++)
	{
		while (fillmins[poziom * (width + 2) + pion] == -1)
		{
			poziom = 1 + rand() % high;
			pion = 1 + rand() % width;
		}
		fillmins[poziom * (width + 2) + pion] = -1;
		////1
		//if (fillmins[(poziom - 1) * (width + 2) + pion - 1] != -1)
		//	fillmins[(poziom - 1) * (width + 2) + pion - 1]++;
		////2
		//if (fillmins[(poziom - 1) * (width + 2) + pion] != -1)
		//	fillmins[(poziom - 1) * (width + 2) + pion]++;
		////3
		//if (fillmins[(poziom - 1) * (width + 2) + pion + 1] != -1)
		//	fillmins[(poziom - 1) * (width + 2) + pion + 1]++;
		////4
		//if (fillmins[poziom * (width + 2) + pion - 1] != -1)
		//	fillmins[poziom * (width + 2) + pion - 1]++;
		////6
		//if (fillmins[poziom * (width + 2) + pion + 1] != -1)
		//	fillmins[poziom * (width + 2) + pion + 1]++;
		////7
		//if (fillmins[(poziom + 1) * (width + 2) + pion - 1] != -1)
		//	fillmins[(poziom + 1) * (width + 2) + pion - 1]++;
		////8
		//if (fillmins[(poziom + 1) * (width + 2) + pion] != -1)
		//	fillmins[(poziom + 1) * (width + 2) + pion]++;
		////9
		//if (fillmins[(poziom + 1) * (width + 2) + pion + 1] != -1)
		//	fillmins[(poziom + 1) * (width + 2) + pion + 1]++;
		for (int i = poziom - 1; i <= poziom + 1; i++)
			for (int j = pion - 1; j <= pion + 1; j++)
				if (fillmins[i*(width + 2) + j] != -1)
					fillmins[i*(width + 2) + j]++;
	}
	for (int i = 1; i < (high + 1); i++)
		for (int j = 1; j < (width + 1); j++)
			mins[(i - 1) * width + j - 1] = fillmins[i * (width + 2) + j];
}
//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable
   if (width <= 0)width = 10;
   if (high <= 0)high = 11;
   if (countofmins <= 0)countofmins = 20;
   NCS = nCmdShow;
   RECT rs;
   rs.top = 25 * high;
   rs.left = 25 * width;
   rs.right = 50 * width;
   rs.bottom = 50 * high;
   AdjustWindowRect(&rs, WS_OVERLAPPEDWINDOW, true);
   flaga = (int*)malloc(sizeof(int)*width*high);
   for (int i = 0; i < width*high; i++)
	   flaga[i] = 0;
   FillMins();
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,
	   rs.left, rs.top, rs.right - rs.left, rs.bottom - rs.top, nullptr, nullptr, hInstance, nullptr);
   parent = hWnd;
   for (int i = 0; i < high; i++) {
	   for (int j = 0; j < width; j++) {
		   HWND h = CreateWindow(szWindowClass, szTitle, WS_CHILD | WS_VISIBLE | WS_BORDER, j * 25, i * 25, 25, 25, hWnd, NULL, hInstance, NULL);
		   SetProp(h, L"flaga", (HANDLE)(i * 10 + j));
	   }
   }
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
			case IDM_DEBUG:
				TrybDebug = !TrybDebug;
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case IDM_CUSTOMSIZE:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, CustomSize);
				break;
			case IDM_NEWGAME:
				ResetWindow = true;
				DestroyWindow(parent);
				break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
	case WM_CREATE:
		SetTimer(parent, 7, 1000, NULL);
		break;
	case WM_TIMER:
		GetTextInfoForKeyMsg(wParam, _T("KEYDOWN"), buf, bufSize); SetWindowText(hWnd, buf);
		break;
	case WM_LBUTTONDOWN:
	{
		int f = (int)GetProp(hWnd, L"flaga");
		if (flaga[f] == 0)
		{
			flaga[f] = 2;
			if (mins[f] == -1)
			{
				bomba = true;
				InvalidateRect(hWnd, NULL, TRUE);
				MessageBox(hWnd, L"Boom!", L"MINE!", MB_OK);
			}
			else if (mins[f] == 0)
			{
				unveilF(f);
			}
			InvalidateRect(hWnd, NULL, TRUE);
		}
	}
	break;
	case WM_RBUTTONDOWN:
	{
		int f = (int)GetProp(hWnd, L"flaga");
		if (flaga[f] != 2)
		{
			if (flaga[f] == 0)
			{
				flaga[f] = 1;
				countofmins--;
			}
			else
			{
				flaga[f] = 0;
				countofmins++;
			}
			InvalidateRect(hWnd, NULL, TRUE);
		}
	}
	break;
    case WM_PAINT:
        {
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			RECT rc;
			GetClientRect(hWnd, &rc);
			int value = 0;
			int f = (int)GetProp(hWnd, L"flaga");
			HBRUSH brush;
			HBRUSH oldBrush;
			if (flaga[f] == 0 || flaga[f] == 2)
			{
				if (flaga[f] == 0)
					value = 0;
				else
					value = 255;
				brush = CreateSolidBrush(RGB(value, 0, 255));
				oldBrush = (HBRUSH)SelectObject(hdc, brush);
				Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
			}
			else
			{
				HBITMAP bitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
				HDC memDC = CreateCompatibleDC(hdc);
				HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, bitmap);
				BitBlt(hdc, 0, 0, 48, 48, memDC, 0, 0, SRCCOPY);
				StretchBlt(hdc, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, memDC, 0, 0, 48, 48, SRCCOPY);
				SelectObject(memDC, oldBitmap);
				DeleteObject(bitmap);
			}
			if (bomba || TrybDebug)
			{
				if (mins[f] == -1)
				{
					brush = CreateSolidBrush(RGB(0, 0, 0));
					oldBrush = (HBRUSH)SelectObject(hdc, brush);
					Ellipse(hdc, (rc.right - rc.left) / 2 - 5, (rc.bottom - rc.top) / 2 - 5, (rc.right - rc.left) / 2 + 5, (rc.bottom - rc.top) / 2 + 5);
				}
			}
			if ((!bomba && flaga[f] == 2) || TrybDebug)
			{
				if (mins[f] > 0)
				{
					TCHAR s[2];
					swprintf_s(s, 2, L"%d", mins[f]);
					TextOut(hdc, (rc.right + rc.left) / 3, (rc.bottom + rc.top) / 3, s, (int)_tcslen(s));
				}

			}
			SelectObject(hdc, oldBrush);
			DeleteObject(brush);

			EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
		if (ResetWindow == false)
			PostQuitMessage(0);
		else
		{
			InitInstance(hInst, NCS);
			ResetWindow = false;
		}
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

INT_PTR CALLBACK CustomSize(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK2)
		{
			width = (int)GetDlgItemInt(hDlg, IDC_EDIT1, NULL, TRUE);
			high = (int)GetDlgItemInt(hDlg, IDC_EDIT2, NULL, TRUE);
			countofmins = (int)GetDlgItemInt(hDlg, IDC_EDIT3, NULL, TRUE);
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if(LOWORD(wParam) == IDCANCEL2)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}