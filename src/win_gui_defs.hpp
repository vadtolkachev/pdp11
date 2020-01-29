#pragma once
#include <Wingdi.h>

template <class DERIVED_TYPE>
BaseWindow<DERIVED_TYPE>::BaseWindow():
    m_hMainWnd(NULL)
{}


template <class DERIVED_TYPE>
LRESULT CALLBACK BaseWindow<DERIVED_TYPE>::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    DERIVED_TYPE *pThis = NULL;

    if(uMsg == WM_NCCREATE)
    {
        CREATESTRUCT *pCreate = (CREATESTRUCT *)lParam;
        pThis = (DERIVED_TYPE *)pCreate->lpCreateParams;
        SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pThis);

        pThis->m_hMainWnd = hWnd;
    }
    else
    {
        pThis = (DERIVED_TYPE *)GetWindowLongPtr(hWnd, GWLP_USERDATA);
    }
    if(pThis)
    {
        return pThis->HandleMessage(uMsg, wParam, lParam);
    }
    else
    {
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
}


template <class DERIVED_TYPE>
HWND BaseWindow<DERIVED_TYPE>::getMainWnd()
{
    return m_hMainWnd;
}


template <class DERIVED_TYPE>
BOOL BaseWindow<DERIVED_TYPE>::create_main_wnd()
{
    WNDCLASS wnd = {};

    wnd.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wnd.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wnd.hInstance = GetModuleHandle(NULL);
    wnd.lpszClassName = ClassName();
    wnd.lpfnWndProc = DERIVED_TYPE::WindowProc;

    if(!RegisterClass(&wnd))
        assert(false);

    m_hMainWnd = CreateWindowEx(0, wnd.lpszClassName, L"pdp-11", WS_BORDER,
        window_x, window_y, window_width, window_height,
        NULL, NULL, GetModuleHandle(NULL), this);

    if(!m_hMainWnd)
    {
        assert(false);
        return FALSE;
    }

    return TRUE;
}
