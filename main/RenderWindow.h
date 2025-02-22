#pragma once

#include "stdafx.h"

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

    int Run(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd);
};

} // namespace zrt
