#include "Graphics.h"

// Create an orthographic projection matrix for 2D rendering.
//D3DXMatrixOrthoLH(&m_orthoMatrix, (float)screenWidth, (float)screenHeight, screenNear, screenDepth);

namespace NS_GraphicsSystem
{
	void Renderer::ThrowIfFailed(HRESULT _hr, char* _msg)
	{
		if (FAILED(_hr))
			throw _msg;
	}

	Renderer::Renderer() : Singleton()
	{
		mDirect = NULL;
		mDevice = NULL;
		fullscreen = false;
		width = height = 200;
	}
	Renderer::~Renderer()
	{
		mDirect->Release();
		mDevice->Release();
	}
	bool Renderer::Initialize(HWND _hw, int _w, int _h, bool _fullscreen)
	{
		hwnd = _hw;
		width = _w;
		height = _h;
		fullscreen = _fullscreen;

		mDirect = Direct3DCreate9(D3D_SDK_VERSION);
		if (mDirect == NULL)
			throw "Directx Initialization failed.";

		InitializeDevice();

		hr = mDirect->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hwnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&mD3D,
			&mDevice
		);
		ThrowIfFailed(hr, "Device creation failed.");

		return true;
	}

	HRESULT Renderer::showBBuffer()
	{
		hr = E_FAIL;
		mDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(127, 127, 127), .0f, 0);
		hr = mDevice->Present(NULL, NULL, NULL, NULL);

		return hr;
	}

	void Renderer::InitializeDevice()
	{
		ZeroMemory(&mD3D, sizeof(mD3D));
		mD3D.BackBufferHeight = height;
		mD3D.BackBufferWidth = width;
		if (fullscreen)
			mD3D.BackBufferFormat = D3DFMT_X8R8G8B8;
		else
			mD3D.BackBufferFormat = D3DFMT_UNKNOWN;
		mD3D.BackBufferCount = 1;
		mD3D.SwapEffect = D3DSWAPEFFECT_DISCARD;
		mD3D.hDeviceWindow = hwnd;
		mD3D.Windowed = (!fullscreen);
		mD3D.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	}
}