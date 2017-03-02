#define WIN32_LEAN_AND_MEAN
#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 600
//Includes
#include <Windows.h>
#include "..\Systems\Graphics\Graphics.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

NS_GraphicsSystem::Renderer* graphics = (NS_GraphicsSystem::Renderer*)NS_GraphicsSystem::Renderer::Instance();

HWND hwnd;
const char* const CLASS_NAME = "WinMain";
const char* const APP_TITLE = "Pixel";
const bool FULLSCREEN = false;

int WINAPI WinMain(HINSTANCE _instance, HINSTANCE _prevInstance, LPSTR _lpcmd, int _cmdShow);
bool CreateMainWnd(HINSTANCE _hinstance, int _int);
LRESULT CALLBACK WndProc(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam);

HINSTANCE hinst;

bool CreateMainWnd(HINSTANCE _hinstance, int _int)
{
	WNDCLASSEX wcx;

	wcx.cbSize = sizeof(wcx);
	wcx.style = CS_HREDRAW | CS_VREDRAW;
	wcx.lpfnWndProc = WndProc;
	wcx.cbClsExtra = 0;
	wcx.cbWndExtra = 0;
	wcx.hInstance = _hinstance;
	wcx.hIcon = NULL;
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcx.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcx.lpszMenuName = NULL;
	wcx.lpszClassName = CLASS_NAME;
	wcx.hIconSm = NULL;

	if (RegisterClassEx(&wcx) == 0)
		return false;
	DWORD style;
	if (FULLSCREEN)
		style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
	else
		style = WS_OVERLAPPEDWINDOW;

	hwnd = CreateWindow(
		CLASS_NAME,
		APP_TITLE,
		style,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		(HWND)NULL,
		(HMENU)NULL,
		_hinstance,
		(LPVOID)NULL);

	if (!hwnd)
		return false;

	ShowWindow(hwnd, _int);
	UpdateWindow(hwnd);

	return true;
}
int WINAPI WinMain(HINSTANCE _instance, HINSTANCE _prevInstance, LPSTR _lpcmd, int _cmdShow)
{
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	MSG msg;
	hwnd = NULL;
	if (!CreateMainWnd(_instance, _cmdShow))
		return false;

	graphics->Initialize(hwnd, WINDOW_WIDTH, WINDOW_HEIGHT, false);

	int done = 0;
	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				done = 1;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			graphics->showBBuffer();
		}
	}
	graphics->Destroy();

	return msg.wParam;
}
LRESULT CALLBACK WndProc(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam)
{
	switch (_msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_CHAR:
		switch (_wparam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			return 0;
		}
	}

	return DefWindowProc(_hwnd, _msg, _wparam, _lparam);
}