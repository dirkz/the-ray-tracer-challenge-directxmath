#include "RenderWindow.h"

#include "Render.h"

namespace zrt
{

constexpr UINT WM_SET_PIXEL = WM_USER + 5;

constexpr float Fov = std::numbers::pi_v<float>;
constexpr POINT MinimumWindowsDimensions{300, 300};

RenderWindow::~RenderWindow()
{
    DeleteObject(m_bitmap);
    DeleteDC(m_hdc);
}

RECT RenderWindow::DesiredRect()
{
    int screenWidth = GetSystemMetrics(SM_CXFULLSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYFULLSCREEN);

    int screenWidthQuarter = screenWidth / 4;
    int screenHeightHalve = screenHeight / 2;

    int left = screenWidthQuarter;
    int right = 3 * screenWidthQuarter;
    int top = 0;
    int height = screenHeightHalve;

    return RECT{left, top, right, height};
}

void RenderWindow::OnInit(HWND hwnd, unsigned width, unsigned height)
{
    m_hwnd = hwnd;

    m_hdc = CreateCompatibleDC(nullptr);
    if (m_hdc == nullptr)
    {
        CheckLastError();
    }
    assert(m_hdc != nullptr);
    m_bitmap = CreateCompatibleBitmap(m_hdc, width, height);
    if (m_bitmap == nullptr)
    {
        CheckLastError();
    }

    m_thread = std::thread{[this, width, height]() {
        auto t1 = Scaling(100, 100, 100);
        Sphere s1{t1};

        PointLight l{Point(-50, 0, -50), Color(1, 1, 1)};

        auto from = Point(0, 0, -200);
        auto to = Point(0, 0, 0);
        auto up = Vector(0, 1, 0);
        auto cameraTransform = ViewTransform(from, to, up);
        Camera camera{width, height, Fov, cameraTransform};

        World world{l, {&s1}};

        Render(camera, world, *this);
    }};
}

void RenderWindow::OnActivate(bool isBeingActivated)
{
}

void RenderWindow::OnResize(unsigned width, unsigned height)
{
    m_windowWidth = width;
    m_windowHeight = height;
}

void RenderWindow::OnRender()
{
    if (m_hwnd == nullptr)
    {
        return;
    }

    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(m_hwnd, &ps);

    BOOL b = BitBlt(hdc, 0, 0, m_windowWidth, m_windowHeight, m_hdc, 0, 0, SRCCOPY);
    if (!b)
    {
        CheckLastError();
    }

    EndPaint(m_hwnd, &ps);
}

void RenderWindow::OnDestroy()
{
    m_thread.join();
}

void RenderWindow::SetPixel(unsigned x, unsigned y, COLORREF color)
{
    HBITMAP oldBitmap = static_cast<HBITMAP>(SelectObject(m_hdc, m_bitmap));

    COLORREF result = ::SetPixel(m_hdc, x, y, color);

    if (result == -1)
    {
        OutputDebugString(L"no SetPixel()\n");
    }

    SelectObject(m_hdc, oldBitmap);

    BOOL b = InvalidateRect(m_hwnd, nullptr, TRUE);
    if (!b)
    {
        OutputDebugString(L"InvalidateRect failed\n");
    }
}

void XM_CALLCONV RenderWindow::operator()(unsigned x, unsigned y, FXMVECTOR color)
{
    XMFLOAT4 floats;
    XMStoreFloat4(&floats, color);

    BYTE r = static_cast<BYTE>(floats.x * 255.f);
    BYTE g = static_cast<BYTE>(floats.y * 255.f);
    BYTE b = static_cast<BYTE>(floats.z * 255.f);

    WPARAM wParam = MAKEWPARAM(x, y);
    LPARAM lParam = RGB(r, g, b);

    BOOL success = PostMessage(m_hwnd, WM_SET_PIXEL, wParam, lParam);
    if (!success)
    {
        CheckLastError();
    }
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

        case WM_SET_PIXEL: {
            WORD x = LOWORD(wParam);
            WORD y = HIWORD(wParam);
            COLORREF color = static_cast<COLORREF>(lParam);
            pCallback->SetPixel(x, y, color);
        }
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
    RECT rect = DesiredRect();

    const wchar_t CLASS_NAME[] = L"TRTCDXMATH";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;

    HWND hwnd = CreateWindowEx(0, CLASS_NAME, L"The Ray Tracer Challenge (DirectXMath)",
                               WS_OVERLAPPEDWINDOW, rect.left, rect.top, width, height, nullptr,
                               nullptr, hInstance, this);

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