#include "RenderWindow.h"

#include "Render.h"

namespace zrt
{

constexpr POINT MinimumWindowsDimensions{300, 300};

constexpr unsigned CanvasWidth = 600;
constexpr unsigned CanvasHeight = 400;

RenderWindow::RenderWindow()
    : m_hwnd{nullptr}, m_canvas{CanvasWidth, CanvasHeight}, m_windowsWidth{0}, m_windowsHeight{0}
{
    m_hdcDesktop = GetDC(nullptr);
    m_hdcMemory = CreateCompatibleDC(m_hdcDesktop);
    m_hbitmap = CreateCompatibleBitmap(m_hdcDesktop, CanvasWidth, CanvasHeight);
    m_hOldBitmap = SelectObject(m_hdcMemory, m_hbitmap);
}

RenderWindow::~RenderWindow()
{
    SelectObject(m_hdcMemory, m_hOldBitmap);
    DeleteDC(m_hdcMemory);
    DeleteObject(m_hbitmap);
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

    m_thread = std::thread{[this, width, height]() {
        constexpr float Fov = std::numbers::pi_v<float> * 0.7f;

        constexpr float Ambient = 0.5f;
        constexpr float Diffuse = 0.7f;
        constexpr float Specular = 0.3f;
        constexpr float Shininess = 10.f;

        StripePattern stripePattern{Color(0, 0.7f, 0.7f), Scaling(5, 5, 5)};

        auto t1 = XMMatrixMultiply(Scaling(10, 10, 10), Translation(8, 0, 0));
        auto mat1 = Material{Colors::Aquamarine, Ambient, Diffuse, Specular, Shininess};
        Sphere s1{t1, mat1};

        auto t2 = XMMatrixMultiply(Scaling(5, 5, 5), Translation(-12, 0, 0));
        auto mat2 = Material{Colors::Wheat, Ambient, Diffuse, Specular, Shininess};
        Sphere s2{t2, mat2};

        auto transformPlane1 =
            XMMatrixMultiply(RotationZ(std::numbers::phi_v<float> / 10.f), Translation(0, -15, 0));
        auto materialPlane1 = PatternedMaterial{stripePattern, Colors::IndianRed, Ambient,
                                                Diffuse,       Specular,          Shininess};
        Plane p1{transformPlane1, materialPlane1};

        PointLight l{Point(-100, 0, 0), Color(1.0f, 1.0f, 1.0f)};

        World world{l, {&s1, &s2, &p1}};

        auto from = Point(0, 0, -20);
        auto to = Point(0, 0, 0);
        auto up = Vector(0, 1, 0);
        auto cameraTransform = ViewTransform(from, to, up);
        Camera camera{CanvasWidth, CanvasHeight, Fov, cameraTransform};

        Render(camera, world, *this);

        OutputDebugString(L"*** rendering finished\n");
    }};
}

void RenderWindow::OnActivate(bool isBeingActivated)
{
}

void RenderWindow::OnResize(unsigned width, unsigned height)
{
    m_windowsWidth = width;
    m_windowsHeight = height;
}

void RenderWindow::OnRender()
{
    if (m_hwnd == nullptr)
    {
        return;
    }

    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(m_hwnd, &ps);

    RECT rect = ps.rcPaint;

    unsigned offsetX = (m_windowsWidth - CanvasWidth) / 2;
    unsigned offsetY = (m_windowsHeight - CanvasHeight) / 2;

    unsigned canvasLeft = rect.left - offsetX;
    unsigned canvasRight = rect.right - offsetX;
    unsigned canvasTop = rect.top - offsetY;
    unsigned canvasBottom = rect.bottom - offsetY;

    for (unsigned y = canvasTop; y < canvasBottom; ++y)
    {
        for (unsigned x = canvasLeft; x < canvasRight; ++x)
        {
            if (x < m_canvas.Width() && y < m_canvas.Height())
            {
                XMVECTOR colorv = m_canvas.GetPixel(x, y);

                XMFLOAT4 color;
                XMStoreFloat4(&color, colorv);

                BYTE r = static_cast<BYTE>(std::round(color.x * 255.f));
                BYTE g = static_cast<BYTE>(std::round(color.y * 255.f));
                BYTE b = static_cast<BYTE>(std::round(color.z * 255.f));

                COLORREF cr = RGB(r, g, b);
                SetPixel(m_hdcMemory, x, y, cr);
            }
        }
    }

    BOOL success =
        BitBlt(hdc, offsetX, offsetY, CanvasWidth, CanvasHeight, m_hdcMemory, 0, 0, SRCCOPY);

    if (!success)
    {
        CheckLastError();
    }

    EndPaint(m_hwnd, &ps);
}

void RenderWindow::OnDestroy()
{
    m_thread.join();
}

void XM_CALLCONV RenderWindow::operator()(unsigned x, unsigned y, FXMVECTOR color)
{
    XMVECTOR clampedColor = XMVectorClamp(color, XMVectorZero(), XMVectorSplatOne());
    m_canvas.SetPixel(x, y, clampedColor);

    unsigned offsetX = (m_windowsWidth - CanvasWidth) / 2;
    unsigned offsetY = (m_windowsHeight - CanvasHeight) / 2;

    LONG left = static_cast<LONG>(x + offsetX);
    LONG top = static_cast<LONG>(y + offsetY);
    LONG right = left + 1;
    LONG bottom = top + 1;

    RECT r{left, top, right, bottom};
    BOOL success = InvalidateRect(m_hwnd, &r, FALSE);
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
    wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));

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