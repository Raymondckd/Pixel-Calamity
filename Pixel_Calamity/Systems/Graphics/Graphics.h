#pragma once
#include "../../Framework/STDSingleton.h"
#include <d3d9.h>
#include <memory>

namespace NS_GraphicsSystem
{
	class Renderer : public Singleton
	{
	private:
		IDirect3D9 * mDirect;
		IDirect3DDevice9* mDevice;
		D3DPRESENT_PARAMETERS mD3D;

		HRESULT hr;
		HWND hwnd;
		bool fullscreen;
		int width, height;

		void InitializeDevice();

		void ThrowIfFailed(HRESULT _hr, char * _msg);
		Renderer();
		~Renderer();
	public:
		bool Initialize(HWND _hw, int _w, int _h, bool _fullscreen);
		HRESULT showBBuffer();
		void Render(float _delta);

	};
}