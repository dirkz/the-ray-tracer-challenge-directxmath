#include "stdafx.h"

#include "RenderWindow.h"

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
                    _In_ PWSTR lpCmdLine, _In_ int nCmdShow)
{
    {
        zrt::RenderWindow rw{};
        rw.Run(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
    }
}