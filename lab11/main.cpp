#ifndef UNICODE
#define UNICODE
#define UNICODE_WAS_UNDEFINED
#endif

#include <Windows.h>
#include <TlHelp32.h>

#ifdef UNICODE_WAS_UNDEFINED
#undef UNICODE
#endif

#define ID_BUTTON_START 228
#define ID_BUTTON_PAUSE 229

#define ID_THREAD_1 1001
#define ID_THREAD_2 2002
#define ID_THREAD_3 3003

HWND hWND;


DWORD WINAPI draw_func_R(LPVOID lpParam) {

        PAINTSTRUCT ps;
        HPEN hPen;

        RECT rect;
        GetClientRect(hWND, &rect);
        rect.bottom = rect.bottom - 100;
        rect.left = rect.left + 290;
        rect.right = rect.right - 500;

        POINT coords = *((POINT*)lpParam);

        HDC hdc = GetDC(hWND);

        hPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
        SelectObject(hdc, hPen);
        MoveToEx(hdc, coords.x, coords.y, NULL);

        while (true) {
            coords.y += 10;
            if (coords.y > 350) {
                coords.y = 5;
                MoveToEx(hdc, coords.x, coords.y, NULL);
                FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));
            }
            else {
                LineTo(hdc, coords.x, coords.y);
            }
            Sleep(20);
            DeleteObject(hPen);
        }

        return 0;
    }

DWORD WINAPI draw_func_G(LPVOID lpParam) {

        PAINTSTRUCT ps;
        HPEN hPen;

        RECT rect;
        GetClientRect(hWND, &rect);
        rect.bottom = rect.bottom - 100;
        rect.left = rect.left + 590;
        rect.right = rect.right - 300;

        POINT coords = *((POINT*)lpParam);

        HDC hdc = GetDC(hWND);

        hPen = CreatePen(PS_SOLID, 5, RGB(0, 255, 0));
        SelectObject(hdc, hPen);
        MoveToEx(hdc, coords.x, coords.y, NULL);

        while (true) {
            coords.y += 10;
            if (coords.y > 350) {
                coords.y = 5;
                MoveToEx(hdc, coords.x, coords.y, NULL);
                FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));
            }
            else {
                LineTo(hdc, coords.x, coords.y);
            }
            Sleep(40);
            DeleteObject(hPen);
        }

        return 0;
    }

    DWORD WINAPI draw_func_B(LPVOID lpParam) {

        PAINTSTRUCT ps;
        HPEN hPen;

        RECT rect;
        GetClientRect(hWND, &rect);
        rect.bottom = rect.bottom - 100;
        rect.left = rect.left + 690;
        rect.right = rect.right;

        POINT coords = *((POINT*)lpParam);

        HDC hdc = GetDC(hWND);

        hPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 255));
        SelectObject(hdc, hPen);
        MoveToEx(hdc, coords.x, coords.y, NULL);

        while (true) {
            coords.y += 10;
            if (coords.y > 350) {
                coords.y = 5;
                MoveToEx(hdc, coords.x, coords.y, NULL);
                FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));
            }
            else {
                LineTo(hdc, coords.x, coords.y);
            }
            Sleep(60);
            DeleteObject(hPen);
        }

        return 0;
    }



HANDLE threads[3];

POINT  coordinates[3] = {
    {300, 5}, {600, 5}, {900, 5}
};

HWND start_button, pause_button;

bool pause_press = true, threads_suspend = false;

LRESULT CALLBACK WndProc(
    HWND   hwnd,
    UINT   msg,
    WPARAM wParam,
    LPARAM lParam
) {

    switch(msg) {

        case WM_CREATE: {

            start_button = CreateWindow(L"Button", L"Start",
                WS_CHILD | WS_VISIBLE | WS_BORDER, 50, 400, 100, 30,
                hwnd, (HMENU)ID_BUTTON_START, NULL, NULL
            );

            pause_button = CreateWindow(
                L"Button", L"Pause",
                WS_CHILD | WS_VISIBLE | WS_BORDER, 175, 400, 100, 30,
                hwnd, (HMENU)ID_BUTTON_PAUSE, NULL, NULL
            );

            break;
        }

        case WM_COMMAND: {

            switch(LOWORD(wParam)) {

                case ID_BUTTON_START: {

                    if(pause_press) {

                        if(threads_suspend) {

                            for(size_t i = 0; i < 3; ++i) {
                                ResumeThread(threads[i]);
                            }

                        } else {

                            threads[0] = CreateThread(NULL, NULL, draw_func_R, &coordinates[0], NULL, NULL);
                            threads[1] = CreateThread(NULL, NULL, draw_func_G, &coordinates[1], NULL, NULL);
                            threads[2] = CreateThread(NULL, NULL, draw_func_B, &coordinates[2], NULL, NULL);

                            threads_suspend = true;

                        }

                        pause_press = false;

                    }

                    break;
                }

                case ID_BUTTON_PAUSE: {

                    if(!pause_press) {

                        for(size_t i = 0; i < 3; ++i) {
                            SuspendThread(threads[i]);
                        }

                        pause_press = true;

                    }

                    break;
                }

            }

            break;
        }

        case WM_GETMINMAXINFO: {

            MINMAXINFO* mmi = (MINMAXINFO*)lParam;
            mmi -> ptMinTrackSize.x = 1000;
            mmi -> ptMinTrackSize.y = 500;
            mmi -> ptMaxTrackSize.x = 1000;
            mmi -> ptMaxTrackSize.y = 500;

            break;
        }

        case WM_CLOSE: {
            DestroyWindow(hwnd);
            break;
        }

        default: {
            return DefWindowProc(hwnd, msg, wParam, lParam);
        }
    }

}

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR     lpCmdLine,
    int       nCmdShow
) {

    MSG        msg;
    HWND       hwnd;
    WNDCLASSEX wc;

    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = L"WindowClass";
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc)) {
        MessageBox(NULL, L"Window registration is failed!", L"Error!", MB_ICONWARNING | MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        L"WindowClass",
        L"OSaN, Lab: 11",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL, NULL, hInstance, NULL
    );

    if(hwnd == NULL) {
        MessageBox(NULL, L"Window creation is failed!", L"Error!", MB_ICONWARNING | MB_OK);
        return 0;
    }

    hWND  = hwnd;

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while(GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}
