#define WIN32_LEAN_AND_MEAN
#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 600
//Includes
#include <Windows.h>



const char* const CLASS_NAME = "WinMain";
const char* const APP_TITLE = "";
int WINAPI WinMain(HINSTANCE _instance, HINSTANCE _prevInstance, LPSTR _lpcmd, int _cmdShow);
bool CreateMainWnd(HINSTANCE _hinstance, int _int);
LRESULT CALLBACK WndProc(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam);

HINSTANCE hinst;




bool CreateMainWnd(HINSTANCE _hinstance, int _int)
{


	return true;
}
int WINAPI WinMain(HINSTANCE _instance, HINSTANCE _prevInstance, LPSTR _lpcmd, int _cmdShow)
{
	WNDCLASSEX wcx;
	HWND hwnd;

	wcx.cbSize = sizeof(wcx);
	wcx.style = CS_HREDRAW | CS_VREDRAW;
	wcx.lpfnWndProc = WndProc;
	wcx.cbClsExtra = 0;
	wcx.cbWndExtra = 0;
	wcx.hInstance = _instance;
	wcx.hIcon = NULL;
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcx.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcx.lpszMenuName = NULL;
	wcx.lpszClassName = CLASS_NAME;
	wcx.hIconSm = NULL;

	if (RegisterClassEx(&wcx) == 0)
		return false;

	hwnd = CreateWindow(
		CLASS_NAME, 
		APP_TITLE, 
		WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT, 
		CW_USEDEFAULT, 
		WINDOW_WIDTH, 
		WINDOW_HEIGHT, 
		(HWND)NULL, 
		(HMENU)NULL, 
		_instance, 
		(LPVOID)NULL);

	if (!hwnd)
		return false;

	ShowWindow(hwnd, _cmdShow);
	UpdateWindow(hwnd);

	return true;
}
LRESULT CALLBACK WndProc(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam)
{


	return NULL;
}







