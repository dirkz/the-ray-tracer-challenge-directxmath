#pragma once

#include "stdafx.h"

#include "Canvas.h"

namespace zrt
{

struct RenderWindow
{
    RenderWindow();

    RECT DesiredRect();

    void OnInit(HWND hwnd, unsigned width, unsigned height);
    void OnActivate(bool isBeingActivated);
    void OnResize(unsigned width, unsigned height);
    void OnRender();
    void OnDestroy();

	void XM_CALLCONV operator()(unsigned x, unsigned y, FXMVECTOR color);

    int Run(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd);

  private:
    std::thread m_thread;
};

} // namespace zrt
