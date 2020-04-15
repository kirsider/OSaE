#include "stdafx.h"
#include "lab9.h"

#define MAX_LOADSTRING 100

HINSTANCE hInst;
TCHAR szTitle[MAX_LOADSTRING];
TCHAR szWindowClass[MAX_LOADSTRING];

HANDLE bmp[4];
int currBmp = 0;

int currX = 0, currY = 0, targX = 0, targY = 0;
bool reverse = true;

#define MOV_STEP 10

ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);


	MSG msg;
	HACCEL hAccelTable;


	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_LAB9, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB9));


	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = 0;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB9));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_LAB9);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance;

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, 800, 600, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	bmp[0] = LoadImage(NULL, L"1.bmp", IMAGE_BITMAP, 64, 80, LR_LOADFROMFILE);
	bmp[1] = LoadImage(NULL, L"2.bmp", IMAGE_BITMAP, 64, 80, LR_LOADFROMFILE);
	bmp[2] = LoadImage(NULL, L"3.bmp", IMAGE_BITMAP, 64, 80, LR_LOADFROMFILE);
	bmp[3] = LoadImage(NULL, L"4.bmp", IMAGE_BITMAP, 64, 80, LR_LOADFROMFILE);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_LBUTTONDOWN:
	{
		targX = LOWORD(lParam) - 50;
		targY = HIWORD(lParam) - 50;
		SetTimer(hWnd, NULL, 100, NULL);
	}
	break;
	case WM_TIMER:
	{
		bool needRedraw = false;
		if (abs(currX - targX) >= MOV_STEP) {
			needRedraw = true;
			if (targX > currX) {
				currX += MOV_STEP;
				reverse = true;
			}
			else {
				currX -= MOV_STEP;
				reverse = false;
			}
		}
		if (abs(currY - targY) >= MOV_STEP) {
			needRedraw = true;
			if (targY > currY)
				currY += MOV_STEP;
			else
				currY -= MOV_STEP;
		}
		if (needRedraw) {
			currBmp = (currBmp + 1) % 4;
			InvalidateRect(hWnd, NULL, true);
			SetTimer(hWnd, NULL, 100, NULL);
		}
	}
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		HDC hCompatibleDC;
		hCompatibleDC = CreateCompatibleDC(hdc);
		SelectObject(hCompatibleDC, bmp[currBmp]);
		if (reverse)
			StretchBlt(hdc, currX, currY, 100, 100, hCompatibleDC, 100, 0, -100, 100, SRCCOPY);
		else
			StretchBlt(hdc, currX, currY, 100, 100, hCompatibleDC, 0, 0, 100, 100, SRCCOPY);
		DeleteDC(hCompatibleDC);

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

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
