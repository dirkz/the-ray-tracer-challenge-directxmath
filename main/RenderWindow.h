#pragma once

#include "stdafx.h"

#include "Canvas.h"

namespace zrt
{

struct RenderWindow
{
    struct PixelSetter
    {
        PixelSetter(RenderWindow &window);

        void XM_CALLCONV operator()(unsigned x, unsigned y, FXMVECTOR color);

      private:
        RenderWindow &m_window;
    };

    RenderWindow();

    RECT DesiredRect();

    void OnInit(HWND hwnd, unsigned width, unsigned height);
    void OnActivate(bool isBeingActivated);
    void OnResize(unsigned width, unsigned height);
    void OnRender();
    void OnDestroy();

    int Run(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd);

  private:
    void XM_CALLCONV SetPixel(unsigned x, unsigned y, FXMVECTOR color);

    PixelSetter m_pixelSetter;
    std::thread m_thread;
};

} // namespace zrt
