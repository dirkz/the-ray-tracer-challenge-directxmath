#include "RenderWindow.h"

namespace zrt
{

constexpr POINT MinimumWindowsDimensions{300, 300};

RenderWindow::RenderWindow()
{
}

void RenderWindow::OnInit(HWND hwnd, unsigned width, unsigned height)
{
}

void RenderWindow::OnActivate(bool isBeingActivated)
{
}

void RenderWindow::OnResize(unsigned width, unsigned height)
{
}

void RenderWindow::OnRender()
{
}

void RenderWindow::OnDestroy()
{
}

static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (uMsg == WM_CREATE)
    {
        LPCREATESTRUCT pCreateStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);
        RenderWindow *pCallback = reinterpret_cast<RenderWindow *>(pCreateStruct->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pCallback));
        return 0;
    }

    RenderWindow *pCallback =
        reinterpret_cast<RenderWindow *>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

    if (pCallback)
    {
        switch (uMsg)
        {
        case WM_DESTROY:
            pCallback->OnDestroy();
            PostQuitMessage(0);
            return 0;

        case WM_PAINT:
            pCallback->OnRender();
            return 0;

        case WM_SIZE: {
            WORD width = LOWORD(lParam);
            WORD height = HIWORD(lParam);
            pCallback->OnResize(width, height);
        }
            return 0;

        case WM_GETMINMAXINFO: {
            LPMINMAXINFO pMinMaxInfo = (LPMINMAXINFO)lParam;
            pMinMaxInfo->ptMinTrackSize = MinimumWindowsDimensions;
        }
            return 0;

        case WM_ACTIVATE: {
            WORD action = LOWORD(wParam);
            std::wstring msg = L"*** WM_ACTIVATE with action " + std::to_wstring(action) + L"\n";
            OutputDebugString(msg.c_str());
            bool isBeingActivated = action != WA_INACTIVE;
            pCallback->OnActivate(isBeingActivated);
        }
            return 0;
        }
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int RenderWindow::Run(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{

    int screenWidth = GetSystemMetrics(SM_CXFULLSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYFULLSCREEN);

    int screenWidthQuarter = screenWidth / 4;
    int screenHeightHalve = screenHeight / 2;

    int left = screenWidthQuarter;
    int right = 3 * screenWidthQuarter;
    int top = 0;
    int width = right - left;
    int height = screenHeightHalve;

    const wchar_t CLASS_NAME[] = L"TRTCDXMATH";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0, CLASS_NAME, L"The Ray Tracer Challenge (DirectXMath)",
                               WS_OVERLAPPEDWINDOW, left, top, width, height, nullptr, nullptr,
                               hInstance, this);

    if (hwnd == NULL)
    {
        return 0;
    }

    OnInit(hwnd, width, height);

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0) != 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return static_cast<char>(msg.wParam);
}

} // namespace zrt